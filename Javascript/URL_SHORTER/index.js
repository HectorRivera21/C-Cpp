require('dotenv').config();
const express = require('express');
const cors = require('cors');
const { urlencoded } = require('body-parser');
const bodyParser = require('body-parser');
const app = express();
const mongoose = require('mongoose');

mongoose.connect(process.env.MONGO_URI, {useNewUrlParser: true, useUnifiedTopology: true});

const Schema = mongoose.Schema;
const Model = mongoose.model;

const SchemaURL = new Schema({
  original_url: String,
  short_url: Number,
});

const Url = Model("Url", SchemaURL);
String.prototype.hashCode = function() {
  var hash = 0,
    i, chr;
  if (this.length === 0) return hash;
  for (i = 0; i < this.length; i++) {
    chr = this.charCodeAt(i);
    hash = ((hash << 5) - hash) + chr;
    hash |= 0; // Convert to 32bit integer
  }
  return hash<0 ? Math.floor(hash/-1000) : Math.floor(hash/1000);
};
const isValidHttpUrl = (string) =>{
  try {
    const newUrl = new URL(string);
    return newUrl.protocol === 'http:' || newUrl.protocol === 'https:';
  } catch (err) {
    return false;
  }
};
const createURL = (Original_Url, Short_Url, done)=>{

  let url = new Url(
  {
    original_url: Original_Url,
    short_url: Short_Url,
  });
  url.save((err,data)=>{
    if(err) return console.error(err);
  });
};

// Basic Configuration
const port = process.env.PORT || 3000;

app.use(cors());

app.use('/public', express.static(`${process.cwd()}/public`));

app.get('/', function(req, res) {
  res.sendFile(process.cwd() + '/views/index.html');
});

//parse json application 
app.use(bodyParser.json());

app.use(urlencoded({extended:true}));
app.post('/api/shorturl', function(req, res) {
  let url = req.body.url;
  if(!isValidHttpUrl(url)){
    res.json({error:"invalid url"});
  }
  else{
    let short_url = url.hashCode();
    createURL(url,short_url);
    res.json({original_url: url, short_url:short_url});
  }
});

app.get('/api/shorturl/:url', (req, res)=>{
  let url = req.params["url"];
  Url.findOne({short_url: url}, (err, data)=>{
    if(err||!data) res.json({error:"invalid url"});
    else 
    {
      res.redirect(data.original_url);
     
    }
  })  
});
app.listen(port, function() {
  console.log(`Listening on port ${port}`);
});
