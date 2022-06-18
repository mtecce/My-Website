const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const messageScheme = new Schema({

    sender: {
        type: String,
        required: true
    },
    content: {
        type: String,
        required: true
    }
}, {timestamps:true});

const Message = mongoose.model('Message',messageScheme);
module.exports = Message;
