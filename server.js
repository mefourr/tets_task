const express = require('express');
const bodyParser = require('body-parser');
const addon = require('./build/Release/addon.node');

const app = express();
const port = 3000;

app.use(express.static('public'));
app.use(bodyParser.json());

app.post('/check-privilege', (req, res) => {
    const { userName } = req.body;
    try {
        const privilege = addon.checkUserPrivilege(userName); // Assuming this is a synchronous call
        res.json({ message: `${privilege}` });
    } catch (error) {
        console.error('Error:', error);
        res.status(500).json({ message: 'Failed to check privilege' });
    }
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});


