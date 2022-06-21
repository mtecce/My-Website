const express = require('express');
const morgan = require('morgan');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const chatRoutes = require('./routes/chatRoutes');
const uri = process.env.MONGODB_URI || 'mongodb+srv://client:CDP_Pass123@chatcluster.lejdwf8.mongodb.net/?retryWrites=true&w=majority';

const app = express();
app.set('view engine','ejs');
app.use(express.static('public'));
app.use(morgan('dev'));
app.use(bodyParser.urlencoded({ extended: true }));

mongoose.connect(uri,{useNewUrlParser: true} )
.then((result) => {
    console.log('connected to db');
})
.catch((err) => console.log(err));

app.listen(process.env.PORT || 3000);

app.get('/',(req,res) => {
    //console.log(req.ip);
    res.render('index');
});

app.get('/csprojects', (req,res) =>{
    res.render('csprojects');
});

app.get('/pictures', (req,res) => {
    let ps = req.url.substring(req.url.indexOf('=')+1);
    res.render('pictures', {pictureset: ps});
});

app.get('/musicprojects', (req,res) => {
    res.render('musicprojects');
});

app.get('/contact', (req,res) =>{
    res.render('contact');
});

app.use('/chat', chatRoutes);