const express = require('express');
const morgan = require('morgan');

const app = express();
app.set('view engine','ejs');
app.use(express.static('public'));
app.use(express.urlencoded({extended: true}));
app.use(morgan('dev'));
app.listen(8080);

app.get('/',(req,res) => {
    console.log(req.ip);
    res.render('index');
});