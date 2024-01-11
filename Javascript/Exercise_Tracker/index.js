const express = require('express')
const app = express()
const cors = require('cors')
require('dotenv').config()
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

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
  username: {type:String, required: true,unique: true,}
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

async function CreateUser(Username) {
  try {
    const user = new User({
      username: Username
    });
    const savedUser = await user.save();
    return savedUser;
  } catch (err) {
    throw err; // Throw the error to be caught by the calling function
  }
}

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:true}));
app.use(cors())
app.use(express.static('public'))

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});

app.get('/api/users', (req, res) => {
  User.find({}).select({_id:1, username:1}).exec((err,data)=>{
    if(err) return res.json({error: err});
    res.json({Users: data});
  });
});
app.post('/api/users', async (req, res) => {
  const user = req.body.username;

  if (user === "" || user === null) {
    res.json({ error: "Invalid UserName" });
  }

  try {
    const existingUser = await User.findOne({ username: user });

    if (existingUser) {
      res.json({ error: "Username already taken" });
    }

    const savedUser = await CreateUser(user);

    res.json({ username: savedUser.username, _id: savedUser._id });
  } catch (err) {
    res.json({ error: err.message });
  }
});
app.post('/api/users/:_id/exercises', (req, res) => {
});
app.get('/api/users/:_id/logs', (req, res) => {
});

const listener = app.listen(process.env.PORT || 3000, () => {
  console.log('Your app is listening on port ' + listener.address().port)
})
