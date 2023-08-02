const express = require('express');
const path = require('path');
const app = express();
const https = require('https');
const fs = require('fs');

/* Only required for accessing app on local network - can be removed */
const os = require('os');
const networkInterfaces = os.networkInterfaces();
const ip = networkInterfaces['eth0'][0]['address'];

// Serve any static files in the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

// GET route for home page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// GET route for '/createbet'
app.get('/createbet', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'createbet.html'));
});

// GET route for '/joinbet'
app.get('/joinbet', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'joinbet.html'));
});

// GET route for '/submitwinner'
app.get('/submitwinner', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'submitwinner.html'));
});

/*
// Standard local server
app.listen(3000, () => {
    console.log('Server listening on port 3000');
});
*/

/* HTTPS server
https.createServer({
    key: fs.readFileSync(path.join(__dirname, 'key.pem')),
    cert: fs.readFileSync(path.join(__dirname, 'cert.pem'))
}, app).listen(3000, '0.0.0.0', () => {
    console.log('Server listening on port 3000');
});
*/

/* Allows mobile to interact */
app.listen(3000, '0.0.0.0', () => {
    console.log('Visit http://localhost:3000 to view the application');
    console.log(`Visit http://${ip}:3000 to view the application`);
});


