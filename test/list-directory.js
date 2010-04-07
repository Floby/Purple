// some modules are included by default and populate the global namespace
// this behaviour can be deactivated in the config file

// we get a hande on the current directory
var d = new system.Directory('./');
// this method name should be changed to something more commonjs.
var list = d.getFileList();
// all elements in list are constructed by system.File() 
// (we can say that this is their 'type')
for(var key in list) {
   echo(key+' -> mime type: ');
   echo(list[key].mimeType);
   echo('<br />');
}
