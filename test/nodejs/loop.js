var interval = 1000; // 1 second
var tick = 1; // 1 second

function timer(){
  console.log("tick tick " + tick++);
}

console.log("started nodejs test process");
setInterval(timer, interval);