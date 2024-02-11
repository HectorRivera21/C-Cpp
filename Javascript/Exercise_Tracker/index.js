const express = require('express')
const app = express()
const cors = require('cors')
require('dotenv').config()
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

mongoose.connect(process.env.MONGO_URI, { useNewUrlParser: true, useUnifiedTopology: true });

const Schema = mongoose.Schema;
const Model = mongoose.model;
const { ObjectId } = mongoose.Types;

const ExerciseSchema = new Schema({
  username: { type: String, required: true },
  description: String,
  duration: Number,
  date: { type: Date, default: Date.now() },
});

const Exercise = Model("Exercise", ExerciseSchema);

const UserSchema = new Schema({
  _id: { type: Number, required: true, unique: true },
  username: { type: String, required: true, unique: true, }
});
const User = Model("User", UserSchema);

const LogSchema = new Schema({
  username: { type: String, required: true },
  count: Number,
  log: [{
    descriptio: String,
    duration: Number,
    date: { type: Date, default: Date.now(), get: date => date.toISOString() },
  }],
});

const Log = Model("Log", LogSchema);

async function CreateUser(Username,UserId) {
  try {
    const user = new User({
      _id: UserId,
      username: Username
    });
    const savedUser = await user.save();
    return savedUser;
  } catch (err) {
    throw err;
  }
}

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cors())
app.use(express.static('public'))

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/views/index.html')
});

app.get('/api/users', async (req, res) => {
  try {
    const users = await User.find({}).select({ _id: 1, username: 1 });

    // Transform the array to ensure each element is an object literal
    const transformedUsers = users.map(user => ({
      _id: user._id,
      username: user.username,
    }));

    res.json(transformedUsers);
  } catch (err) {
    res.json({ error: err.message });
  }
});
app.post('/api/users', async (req, res) => {
  const user = req.body.username;

  if (user === "" || user === null) {
    res.json({ error: "Invalid UserName" });
  }

  try {
    const highestIdUser = await User.findOne().sort({ _id: -1 }); // Find the user with the highest _id
    const newUserId = highestIdUser ? highestIdUser._id + 1 : 1; // Increment the _id for the new user

    const existingUser = await User.findOne({ username: user });

    if (existingUser) {
      res.json({ error: "Username already taken" });
    }

    const savedUser = await CreateUser(user, newUserId);

    res.json({ username: savedUser.username, _id: savedUser._id });
  } catch (err) {
    res.json({ error: err.message });
  }
});
app.post('/api/users/:_id/exercises', async (req, res) => {
  const userId = req.params._id;
  const { description, duration, date } = req.body;

  try {
    const ob = new ObjectId(userId);

    const user = await User.findOne({_id: ObjectId(userId)});

    if (!user) {
      return res.json({ error: "User not found" });
    }

    // Create a new exercise
    const exercise = {
      description,
      duration,
      date: date || Date.now(), // If date is not provided, use the current date
    };

    // Add the exercise to the user's log
    user.log.push(exercise);

    // Increment the count
    user.count = user.log.length;

    // Save the updated user
    await user.save();

    // Return the updated user object
    res.json({
      _id: user._id,
      username: user.username,
      count: user.count,
      log: user.log,
      description: exercise.description,
      duration: exercise.duration,
      date: exercise.date.toDateString(), // Format date as a string
    });
  } catch (err) {
    res.json({ error: err.message });
  }
});
app.get('/api/users/:_id/logs', async(req, res) => {
  const { from, to, limit } = req.query;
  try {
    const user = await User.findById(req.params._id);
    res.json(user);
  } catch (err) {
    res.json({ error: err.message });
  }
});

const listener = app.listen(process.env.PORT || 3000, () => {
  console.log('Your app is listening on port ' + listener.address().port)
})
