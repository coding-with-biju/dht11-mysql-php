const express = require('express');
const bodyParser = require('body-parser');
const mysql = require('mysql2');

const app = express();
const port = 3000;

// Database configuration
const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'dht11_data'
});

db.connect((err) => {
    if (err) throw err;
    console.log('Connected to MySQL database!');
});

// Middleware
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Route to handle incoming data
app.post('/send-data', (req, res) => {
    const { temperature, humidity } = req.body;

    if (!temperature || !humidity) {
        return res.status(400).send('Missing data');
    }

    const query = 'INSERT INTO readings (temperature, humidity) VALUES (?, ?)';
    db.query(query, [temperature, humidity], (err) => {
        if (err) throw err;
        console.log('Data inserted into database:', { temperature, humidity });
        res.status(200).send('Data saved successfully');
    });
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});
