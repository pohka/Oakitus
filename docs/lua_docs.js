let docsMain;
let docsContext;

function sortByKey(array, key) {
  return array.sort(function(a, b) {
      var x = a[key]; var y = b[key];
      return ((x < y) ? -1 : ((x > y) ? 1 : 0));
  });
}

function getFuncSignatureString(func)
{
  let signature = func.return + " " + func.name + "(";
      
  if(func.params !== undefined)
  {
    for(let a=0; a<func.params.length; a++)
    {
      signature += func.params[a].type + " " + func.params[a].name;
      if(a < func.params.length-1)
      {
        signature += ", ";
      }
    }
  }
  signature += ")";
  return signature;
}

function classEntry(key, data)
{
  let str = "<h2 id=\"class_" + key + "\">" + key + "</h2>";

  //variables table
  if(data.vars !== undefined)
  {
    str += "<table>" +
    "<tr>" + 
      "<th>Var Name</th>" +
      "<th>Type</th>" +
    "</tr>";

    for(let varName in data.vars)
    {
      str += "<tr>" +
          "<td>" + varName + "</td>" +
          "<td>" + data.vars[varName] + "</td>" +
        "</tr>";
    }

    str += "</table>";
  }
  
  //functions table
  if(data.funcs !== undefined)
  {
    str += "<table>" +
      "<tr>" + 
        "<th>Function</th>" +
        "<th>Signature</th>" +
        "<th>Description</th>" +
      "</tr>";

    let funcs = sortByKey(data.funcs, "name");

    for(let i=0; i < funcs.length; i++)
    {
      let signature = getFuncSignatureString(funcs[i]);
      str += "<tr>" +
          "<td>" + funcs[i].name + "</td>" +
          "<td><code>" + signature + "</code></td>" +
          "<td>" + funcs[i].desc + "</td>" +
        "</tr>";
    }

    str += "</table>"
  }

  docsMain.innerHTML += str;
}

function constantEntry(key, data)
{
  let str = "<h3 id=\"constant_" + key + "\">" + key + "</h3>";
  
  str += "<table>" +
  "<tr>" + 
    "<th>Name</th>" +
    "<th>Value</th>" +
    "<th>Description</th>" +
  "</tr>";

  for(let i=0; i<data.length; i++)
  {
    str += "<tr>" +
        "<td>" + data[i].name + "</td>" +
        "<td>" + data[i].value + "</td>" +
        "<td>" + data[i].desc + "</td>" +
      "</tr>";
  }

  str += "</table>";

  docsMain.innerHTML += str;
}

window.onload = function(){
  docsMain = document.getElementById("docs-main");
  docsContext = document.getElementById("docs-context");

  //fetch data
  fetch('lua_docs.json')
  .then(function(response) {
    return response.json();
  })
  .then(function(data) {
    console.log(data);

    //sort classes
    const orderedClasses = {};
    Object.keys(data.classes).sort().forEach(function(key) {
      orderedClasses[key] = data.classes[key];
    });

    //main container
    //-----------------------------------------
    //put global functions at top of table
    const GLOBAL_ENTRY = "_G";
    if(orderedClasses[GLOBAL_ENTRY] !== undefined)
    {
      classEntry(GLOBAL_ENTRY, orderedClasses[GLOBAL_ENTRY]);
    }

    //loop through all classes
    for (let key in orderedClasses)
    {
      if(key != GLOBAL_ENTRY)
      {
        classEntry(key, orderedClasses[key])
      }
    }

    docsMain.innerHTML += "<br><br><br><hr><br>"

    const constants = {};
    Object.keys(data.constants).sort().forEach(function(key) {
      constants[key] = data.constants[key];
    });
    for(let key in constants)
    {
      constantEntry(key, constants[key]);
    }

    //table of contents
    //-------------------------
    docsContext.innerHTML += "<h3>Classes</h3>";

    if(orderedClasses[GLOBAL_ENTRY] !== undefined)
    {
      docsContext.innerHTML += "<a href=\"#class_" + GLOBAL_ENTRY  + "\">" + GLOBAL_ENTRY + "</a>";
    }

    //loop through all classes
    for (let key in orderedClasses)
    {
      if(key != GLOBAL_ENTRY)
      {
        docsContext.innerHTML += "<a href=\"#class_" + key  + "\">" + key + "</a>";
      }
    }

    docsContext.innerHTML += "<br><h3>Constants</h3>";

    for(let key in constants)
    {
      docsContext.innerHTML += "<a href=\"#constant_" + key  + "\">" + key + "</a>";
    }
  });
}


