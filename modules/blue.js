function process_template(template) {
    // simple substitution from <%= /* */ %> forms to <% echo() %>
    var template = template.replace(/<%=(.*)%>/g, "<% echo($1); %>");
    var expecting = 'begin';
    var last = "";
    var buffer = "";
    var result = "";
    for(var i=0 ; i<template.length ; ++i) {
	switch(template[i]) {
	    case '<':
		if(expecting == 'begin' && template[i+1] == '%') {
		    ++i;
		    result += "__print("+JSON.stringify(buffer)+");";  
		    buffer = '';
		    expecting = 'end';
		}
		else {
		    buffer += template[i];
		}
		break;
	    case '%':
		if(expecting == 'end' && template[i+1] == '>') {
		    ++i; 
		    result += buffer;
		    buffer = '';
		    expecting = 'begin';
		}
		else {
		    buffer += template[i];
		}
		break;
	    case '\\': 
		if(expecting == 'begin') {
		    buffer += template[i+1];
		    ++i;
		}
		break;
	    default:
		buffer += template[i];
		break;
	}
	last = template[i];
    }
    if(expecting == 'begin') {
	result += "__print("+JSON.stringify(buffer)+");";
    }
    return result;
}

var exports = process_template;
