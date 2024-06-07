const express = require('express')
const app = express()
const cors = require('cors')
require('dotenv').config()
const mongoose = require('mongoose');
const ObjectId = require('mongoose').Types.ObjectId;
const bodyParser = require('body-parser');

mongoose.connect(process.env.MONGO_URI, { useNewUrlParser: true, useUnifiedTopology: true });

const Schema = mongoose.Schema;
const Model = mongoose.model;

const UserSchema = new Schema({
  username: { type: String, required: true, unique: true, },
  exercises: [{
    description: String,
    duration: Number,
    date: Date
  }]
});
const User = Model("User", UserSchema);const ERROR = { error: "There was an error while getting the users." };

async function CreateUser(Username) {
  try {
    const user = new User({
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
    const array = users.map(user => ({ _id: user._id, username: user.username }));
    res.json(array);
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
    const savedUser = await CreateUser(user);

    res.json({ username: savedUser.username, _id: savedUser._id });
  } catch (err) {
    res.json({ error: err.message });
  }
});
app.post('/api/users/:_id/exercises', async (req, res) => {
  const id = req.params._id;
  let { description, duration, date } = req.body;
  if (date) {
    date = date.split('-');
    date = new Date(date[0],date[1]-1,date[2]);
  }
  else 
  {
    date = new Date().toDateString();
  }

    const newExercise = {
        description: description,
        duration: duration,
        date: date
    };
  console.log(newExercise.date)
    User.findOne({ _id: new ObjectId(id) }, (err, data) => {
            if (err) return res.send(ERROR)
            data.exercises.push(newExercise);
            data.save((err, data) => {
                const response = {
                    _id: data._id,
                    username: data.username,
                    date: new Date(data.exercises[data.exercises.length - 1].date).toDateString(),
                    duration: data.exercises[data.exercises.length - 1].duration,
                    description: data.exercises[data.exercises.length - 1].description,
                };

                res.json(response)
            })
        }
    )
});
app.get('/api/users/:_id/logs',  (req, res) => {
  const id = req.params._id;
  const dateFrom = new Date(req.query.from);
    const dateTo = new Date(req.query.to);
    const limit = parseInt(req.query.limit);

    User.findOne({ _id: new ObjectId(id) }, (err, data) => {
        if (err) return res.send(ERROR)

        let log = [];

        data.exercises.filter(exercise =>
            new Date(Date.parse(exercise.date)).getTime() > dateFrom
            && new Date(Date.parse(exercise.date)).getTime() < dateTo
        )

        for (const exercise of data.exercises) {
            log.push({
                description: exercise.description,
                duration: exercise.duration,
                date: new Date(exercise.date).toDateString()
            })
        }

        if (limit) log = log.slice(0, limit)

        res.json({
            _id: data._id,
            username: data.username,
            count: log.length,
            log: log
        })
      })
});

const listener = app.listen(process.env.PORT || 3000, () => {
  console.log('Your app is listening on port ' + listener.address().port)
})
