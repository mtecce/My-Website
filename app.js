const express = require('express');
const createApplication = require('express/lib/express');
const { append } = require('express/lib/response');
const morgan = require('morgan');

const app = express();
app.set('view engine','ejs');
app.use(express.static('public'));
app.use(express.urlencoded({extended: true}));
app.use(morgan('dev'));
app.listen(process.env.PORT || 3000);

app.get('/',(req,res) => {
    console.log(req.ip);
    res.render('index');
});

app.get('/csprojects', (req,res) =>{
    res.render('csprojects');
});

app.get('/musicprojects', (req,res) => {
    res.render('musicprojects')
});

app.get('/contact', (req,res) =>{
    res.render('contact');
});