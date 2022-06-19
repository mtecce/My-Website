const Message = require('../models/message');

let timeCounter = 0;
const deleteTime = 10000;

const get_page = (req,res) => {
    let username = req.url.substring(req.url.indexOf('=')+1);
    //console.log(username);
    Message.find().sort()
        .then((result) => {
            res.render('chat',{user: username, messages:result});
        })
        .catch((err) => {
            console.log(err)
        })
};

const add_message = (req,res) => {
    const nm = new Message(req.body);
    nm.save()
        .then(() => {
            console.log('saved message');
        })
        .catch((err) => {
            console.log(err);
        })
};

const delete_message = (req,res) => {
    Message.findByIdAndDelete(String(req.body.id))
        .catch(err => console.log(err));
};

module.exports = {
    get_page,
    add_message,
    delete_message
}