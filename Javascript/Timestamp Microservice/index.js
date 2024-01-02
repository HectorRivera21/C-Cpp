"use strict";
// index.js
// where your node app starts
require('dotenv').config();
// init project
var express = require('express');
var app = express();

// enable CORS (https://en.wikipedia.org/wiki/Cross-origin_resource_sharing)
// so that your API is remotely testable by FCC 
var cors = require('cors');
app.use(cors({optionsSuccessStatus: 200}));  // some legacy browsers choke on 204

// http://expressjs.com/en/starter/static-files.html
app.use(express.static('public'));

// http://expressjs.com/en/starter/basic-routing.html
app.get("/",(req, res) =>{
  res.sendFile(__dirname + '/views/index.html');
});


// your first API endpoint... 
app.get("/api/hello", (req, res) =>{
  res.json({greeting: 'hello API'});
});
app.get("/api/", (req, res) =>{
  res.json({unix: Date.now(), utc:`${new Date().toUTCString()}`});
});
app.get("/api/:date", (req, res) =>{

  let date = req.params["date"];
  var newDate = "";
  var timestamp = 0;
  if(/\d{5,}/.test(date)){
    date = parseInt(date);
    newDate = new Date(date).toUTCString();
    timestamp = (date);
  }
  else 
  {
    newDate = new Date(date).toUTCString();
    timestamp  = Date.parse(date);
  }
  
  if(newDate === "Invalid Date"){
    res.json({error:"Invalid Date"})
  }
  else 
  {
    res.json({unix:timestamp, utc: newDate});
  }
});



// listen for requests :)
var listener = app.listen(process.env.PORT, () =>{
  console.log('Your app is listening on port ' + listener.address().port);
});
