var critical = {
    a: 0,
    b: 0
};

var threads = require('threads');
var MyThread = function MyThread(res) {
    threads.Thread.apply(this, args);
    this.criticalResource = res;
}
//this is a very nasty class declaration
//but it is the native JS way
MyThread.prototype = {__proto__: threads.Thread.prototype};
MyThread.prototype.run = function run() {
    var self = this;
    threads.synchronized(this.criticalResource, function(){
	self.criticalResource.a++;
	self.criticalResource.b--;
    });
}

var t1 = new MyThread(critical);
var t2 = new MyThread(critical);
t1.run();
t2.run();

t1.join();
t2.join();

echo(JSON.encode(critical));
