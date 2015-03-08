var http = require("http");
var fs = require('fs');
var Relayr = require('relayr');

var app_id = "d190a5f0-940a-4e1a-a19e-c418d03b22cf";
var dev_id = "5d0f5cac-cd72-4c01-9520-59ff44a8c62c";
var token  = "klxnVy6xFbLUjOY09wGwde1GGyf9stbb";
var lcp = "5d0f5cac-cd72-4c01-9520-59ff44a8c62c";

var relayr = new Relayr(app_id);


function prettyJSON(obj) {
    console.log(JSON.stringify(obj, null, 2));
}

http.createServer(function(request, response) {
  response.writeHead(200, {"Content-Type": "text/plain"});
  response.write("Relayr");

  // relayr.on('data', function (topic, msg) {
  //   console.log(topic + ":" + msg);
  //   fs.appendFile('/home/epic/Desktop/hi.txt', topic ":" + msg + "\n", function(err){
  //     if(err) throw err;
  //   })
  // });


  relayr.deviceModel(token, lcp, function (err, description) {
  console.log("-------------- Light, Color & Proximity ------------------");
  console.log(err||description);
  console.log("----------------------------------------------------------");

  });

  relayr.connect(token, lcp);
  relayr.on('connect', function () {
  });
  relayr.on('data', function(topic, msg) {
  console.log("TOPIC:"+topic);
  console.log(msg);
  fs.appendFile('/home/epic/Desktop/LightProx.txt', msg.readings[0].value + "\n", function(err){
    if(err) throw err;
  });
  });


  response.end();
}).listen(8888);
