const express = require('express')
const app = express()
const cors = require('cors')
require('dotenv').config()
const mongoose = require('mongoose');

mongoose.connect(process.env.MONGO_URI, {useNewUrlParser: true, useUnifiedTopology: true});

const Schema = mongoose.Schema;
const Model = mongoose.model;

const ExerciseSchema = new Schema({
  username: {type: String, required: true},
  description: String,
  duration: Number,
  date: {type: Date, default: Date.now()},
});

const Exercise = Model("Exercise", ExerciseSchema);

const UserSchema = new Schema({
  username: {type:String, required: true}
});
const User = Model("User", UserSchema);

const LogSchema = new Schema({
  username: {type: String, required:true},
  count: Number,
  log: [{
    description: String,
    duration: Number,
    date: {type: Date, default: Date.now()}, 
  }],
});

const Log = Model("Log", LogSchema);

app.use(cors())
app.use(express.static('public'))
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});

app.get('/api/users', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});
app.post('/api/users', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});

app.post('/api/users/:_id/exercises', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});
app.get('/api/users/:_id/logs', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});





const listener = app.listen(process.env.PORT || 3000, () => {
  console.log('Your app is listening on port ' + listener.address().port)
})
