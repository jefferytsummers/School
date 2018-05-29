function Initiate()
{
    var file     = "cgi-bin/p3.py";
    var messages = document.getElementById("messages");
    var request  = new XMLHttpRequest();
    var check    = "alice: hello <br/> bob: whatever <br/>";
    request.open("GET", file, 1);
    console.log(request.responseText);
    request.onreadystatechange = function ()
    {
        if(request.status === 200 || request.status === 0)
        {
            messages.innerHTML = request.responseText;
            var str = request.responseText.trim().split("<br/>").filter(function(a){return a.length > 1;});
            var names = [];
            for(var k = 0; k < str.length; ++k)
                names.push(str[k].split(":")[0]);
            if(names.length > 2)
                sessionStorage.setItem("name", names.slice(-1)[0]);
            else
                sessionStorage.setItem("name", "");
            document.getElementById("name").value = sessionStorage.getItem("name");
        }
    }
    request.send(null);

    var button = document.getElementById("clear");
    button.addEventListener("click", clear_session_storage);
}

function clear_session_storage()
{
    sessionStorage.clear();
}

window.addEventListener("load", Initiate);