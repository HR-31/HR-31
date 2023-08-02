import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM buys WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])

    # Calculate total value of each holding and the total value of stocks
    total_value = 0
    for stock in stocks:
        quote = lookup(stock['symbol'])
        stock['price'] = usd(quote['price'])
        stock['total'] = usd(quote['price'] * stock['total_shares'])
        total_value += quote['price'] * stock['total_shares']

    # Get cash balance
    rows = db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"])
    cash = rows[0]['cash']

    # Calculate grand total
    grand_total = total_value + cash

    return render_template("index.html", stocks=stocks, cash=usd(cash), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Ensure user enters symbol
        if not request.form.get("symbol"):
            return apology("Must enter symbol", 400)

        # Performing lookup function using API on symbol provided by user
        stock = lookup(request.form.get("symbol"))

        # Ensuring the symbol provided exists
        if not stock:
            return apology("Symbol does not exist", 400)

        shares = request.form.get("shares")

        # Ensuring shares value is submitted
        if not shares:
            return apology("Must enter shares value", 400)

        # Check if shares value is integer
        if not shares.isdecimal():
            return apology("Shares must be a nonnegative integer", 400)

        # Getting the amount of cash this user holds
        rows = db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"])
        cash = rows[0]['cash']
        symbol = stock['symbol']
        shares = int(request.form.get("shares"))
        price = stock['price']
        buys = "Buy order"

        if cash >= (shares * price) > 0:
            db.execute("INSERT INTO buys (user_id, symbol, shares, price, bs) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], symbol, shares, price, buys)

            updated_cash = cash - (shares * price)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, session["user_id"])

        else:
            return apology("You don't have enough money, broke ass...", 400)

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, shares, price, time, bs FROM buys WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'GET':
        return render_template("quote.html")

    else:
        x = request.form.get("symbol")

        if not x:
            return apology("Must input symbol", 400)

        data = lookup(x)

        if data:
            return render_template("quoted.html", data=data)

        else:
            return apology("Invalid symbol", 400)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Check database whether username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if rows != []:
            return apology("username already exists", 400)

        password = request.form.get("password")

        # Ensure password submitted
        if not password:
            return apology("must enter password", 400)

        if len(password) < 5:
            return apology("password must be longer than 4 characters", 400)

        if not any(char.isdigit() for char in password):
            return apology("password must contain a number", 400)

        def is_symbol(ch):
            symbols = set('!@#$%^&*()-_=+{[]}|;:,.<>/?`~')
            return ch in symbols

        if not any(is_symbol(char) for char in password):
            return apology("password must contain a symbol", 400)

        # Ensure confirmation submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # Ensure password and confirmation match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and password confirmation do not match", 400)

        # Insert user submission into database
        username = request.form.get("username")
        password = request.form.get("password")
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=10)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Fetch stocks from database
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM buys WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)

    # Reached website via POST
    else:
        symbol = request.form.get("symbol")

        # Ensure user enters symbol
        if not symbol:
            return apology("Must select stock to sell\n dummy...", 400)

        shares = request.form.get("shares")
        # Check if shares value is integer
        if not shares.isdecimal():
            return apology("Shares must be a nonnegative integer", 400)

        # Assigning variables for database INSERT below
        shares = int(request.form.get("shares"))
        sells = "Sell order"

        # Finding today's price of stock
        stock_info = lookup(symbol)
        price = stock_info['price']

        # Get user cash balance
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]['cash']

        selling_stock = [stock['total_shares'] for stock in stocks if stock['symbol'] == symbol]
        total_shares = selling_stock[0]

        # Ensuring user has enough shares to sell the amount requested
        if shares <= total_shares:
            db.execute("INSERT INTO buys (user_id, symbol, shares, price, bs) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], symbol, -shares, price, sells)

            # Update cash balance post-sale
            updated_cash = cash + (shares * price)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, session["user_id"])

        else:
            return apology("You don't have enough shares.", 400)

        # Redirect user to home page
        return redirect("/")
