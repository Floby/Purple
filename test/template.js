var templateData = {
    title: "mon titre",
    a: 8,
    b: request.get.param
};

// blue is the template engine
var blue = require('blue');
var result = blue.execute("./template.thtml", templateData);
// this is not the pro 'way' to output the result but it's way shorter
// php-like utilities can be deactivated in the config file
echo(result);
