const express = require('express');
const createApplication = require('express/lib/express');
const { append } = require('express/lib/response');
const morgan = require('morgan');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const Message = require('./models/message');

const uri = process.env.MONGODB_URI || 'mongodb+srv://client:CDP_Pass123@chatcluster.lejdwf8.mongodb.net/?retryWrites=true&w=majority';


const app = express();
app.set('view engine','ejs');
app.use(express.static('public'));
app.use(express.urlencoded({extended: true}));
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

app.get('/musicprojects', (req,res) => {
    res.render('musicprojects')
});

app.get('/contact', (req,res) =>{
    res.render('contact');
});

app.get('/chat',(req,res) => {
    let username = req.url.substring(req.url.indexOf('=')+1);
    //console.log(username);
    Message.find().sort()
        .then((result) => {
            res.render('chat',{user: username, messages:result});
        })
        .catch((err) => {
            console.log(err)
        })
});

app.get('/messages', (req,res) => {
    Message.find().sort()
        .then((result) => {
            res.render('messages',{messages:result});
        })
        .catch((err) => {
            console.log(err)
        })
});

app.post('/chat', (req,res) => {
    const nm = new Message(req.body);
    nm.save()
        .then(() => {
            console.log('saved message');
        })
        .catch((err) => {
            console.log(err);
        })
});

module.exports = mongoose;