-- Keep a log of any SQL queries you execute as you solve the mystery: 

-- What happened on 28, 7, 2021:
SELECT description FROM crime_scene_reports
    WHERE year = '2021'
    AND month = '7'
    AND day = '28';

-- What did the witnesses say:
SELECT * FROM interviews
    WHERE transcript LIKE "%bakery%"
    AND month = '7';

-- What is license plate of getaway car:
SELECT * FROM bakery_security_logs
    WHERE day = '28'
    AND month = '7'
    AND activity = 'exit'
    AND hour = '10'
    AND minute > '15'
    AND minute < '25';

-- What is closest airport:
SELECT * FROM airports;

-- What is the earliest flight to leave CSF on 29th July 2021 and where was it going:
SELECT * FROM flights
    WHERE origin_airport_id = '8'
    AND day = '29'
    ORDER BY hour, minute
    LIMIT 1;

-- Which airport had ID = 4:
SELECT * FROM airports;

-- What were the passport numbers of the passengers on the flight above:
SELECT passport_number FROM passengers
    WHERE flight_id IN

        (SELECT id FROM flights
            WHERE origin_airport_id = '8'
            AND day = '29'
            ORDER BY hour, minute
            LIMIT 1);

-- Which passport numbers from above match with the passport numbers of the people leaving bakery:

SELECT name, passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
   WHERE day = '28'
    AND month = '7'
    AND activity = 'exit'
    AND hour = '10'
    AND minute > '15'
    AND minute < '25')

    AND

    passport_number IN
    (SELECT passport_number FROM passengers
        WHERE flight_id IN

            (SELECT id FROM flights
                WHERE origin_airport_id = '8'
                AND day = '29'
                ORDER BY hour, minute
                LIMIT 1));

-- Show me all data for ATM withdrawals on Leggett Street on 28, 7, 2021:
SELECT * FROM atm_transactions
    WHERE atm_location = 'Leggett Street'
    AND month = '7'
    AND day = '28'
    AND transaction_type = 'withdraw';

-- Who owns the account numbers of the withdrawals from above:
SELECT name FROM people
    WHERE id IN

        (SELECT person_id FROM bank_accounts
            WHERE account_number IN

            (SELECT account_number FROM atm_transactions
                WHERE atm_location = 'Leggett Street'
                AND month = '7'
                AND day = '28'
                AND transaction_type = 'withdraw'));

-- Which person was on THE flight, left THE bakery and withdrew money at THE atm:
SELECT name FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = '28'
        AND month = '7'
        AND activity = 'exit'
        AND hour = '10'
        AND minute > '15'
        AND minute < '25')

        AND

        passport_number IN
        (SELECT passport_number FROM passengers
            WHERE flight_id IN

                (SELECT id FROM flights
                    WHERE origin_airport_id = '8'
                    AND day = '29'
                    ORDER BY hour, minute
                    LIMIT 1))

        AND

        id IN
        (SELECT person_id FROM bank_accounts
        WHERE account_number IN

        (SELECT account_number FROM atm_transactions
            WHERE atm_location = 'Leggett Street'
            AND month = '7'
            AND day = '28'
            AND transaction_type = 'withdraw'));

-- What calls less than 60s were made on 28th July? Any by Luca or Bruce?
SELECT * FROM phone_calls
    WHERE month = '7'
    AND day = '28'
    AND duration < 60;

-- What were the 'caller' numbers of the above:
SELECT caller FROM phone_calls
    WHERE month = '7'
    AND day = '28'
    AND duration < 60;

-- Who is the THIEF:
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
   WHERE day = '28'
    AND month = '7'
    AND activity = 'exit'
    AND hour = '10'
    AND minute > '15'
    AND minute < '25')

    AND

    passport_number IN
    (SELECT passport_number FROM passengers
        WHERE flight_id IN

            (SELECT id FROM flights
                WHERE origin_airport_id = '8'
                AND day = '29'
                ORDER BY hour, minute
                LIMIT 1))

    AND

    id IN
    (SELECT person_id FROM bank_accounts
    WHERE account_number IN

    (SELECT account_number FROM atm_transactions
        WHERE atm_location = 'Leggett Street'
        AND month = '7'
        AND day = '28'
        AND transaction_type = 'withdraw'))

    AND

    phone_number IN
    (SELECT caller FROM phone_calls
        WHERE month = '7'
        AND day = '28'
        AND duration < 60);

-- Who is the accomplice:
SELECT name FROM people
    WHERE phone_number IN

    (SELECT receiver FROM phone_calls
        WHERE month = '7'
        AND day = '28'
        AND duration < 60
        AND caller IN

            (SELECT phone_number FROM people
                WHERE name = 'Bruce'));