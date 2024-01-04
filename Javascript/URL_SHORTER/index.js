require('dotenv').config();
const express = require('express');
const cors = require('cors');
const dns = require('dns');
const { urlencoded } = require('body-parser');
const bodyParser = require('body-parser');
const app = express();
let db = {};
String.prototype.hashCode = function() {
  var hash = 0,
    i, chr;
  if (this.length === 0) return hash;
  for (i = 0; i < this.length; i++) {
    chr = this.charCodeAt(i);
    hash = ((hash << 5) - hash) + chr;
    hash |= 0; // Convert to 32bit integer
  }
  return hash/1000;
}
const isValidHttpUrl = (string) =>{
  try {
    const newUrl = new URL(string);
    return newUrl.protocol === 'http:' || newUrl.protocol === 'https:';
  } catch (err) {
    return false;
  }
}

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
    db[short_url]=url;
    res.json({original_url: url, short_url:short_url});
  }
});

app.get('/api/shorturl/:url', (req, res)=>{
  let url = req.params["url"];
  if(url in db){
    res.redirect(db[url]);
  }
  else{
    res.json({error:"invalid url"});
  }
  
});
app.listen(port, function() {
  console.log(`Listening on port ${port}`);
});
