const express = require('express');
const chatController = require('../controllers/chatController');
const router = express.Router();

router.get('/', chatController.get_page);
router.post('/', chatController.add_message);
router.delete('/', chatController.delete_message);

module.exports = router;