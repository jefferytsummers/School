function Initiate()
{
    var c           = document.getElementById("canvas");
    var ctx         = c.getContext("2d");
    var l           = document.getElementById("canvas_size").value;
    var r           = l/2;
    c.width         = l;
    c.height        = l;

    ctx.beginPath();
    ctx.arc(r, r, r, 0, 2*Math.PI, true);
    ctx.strokeStyle = 'yellow';
    ctx.stroke();
    ctx.fillStyle   = 'yellow';
    ctx.fill();
}

function Fire()
{
    document.getElementById("gunshot").play();
    var c     = document.getElementById("canvas");
    var ctx   = c.getContext("2d");
    var l     = document.getElementById("canvas_size").value;
    var r     = l/2;
    var darts = document.getElementById("darts").value;
    var pi = 0;

    c.classList.add("display");
    c.width  = l;
    c.height = l;

    ctx.beginPath();
    ctx.arc(r, r, r, 0, 2*Math.PI, true);
    ctx.strokeStyle = 'yellow';
    ctx.stroke();
    ctx.fillStyle   = 'yellow';
    ctx.fill();

    for(var i = 0; i < darts; ++i)
    {
        var x = Math.floor(Math.random()*l)%l;
        var y = Math.floor(Math.random()*l)%l;
        ctx.beginPath();
        if(Math.sqrt((r-x)*(r-x) + (r-y)*(r-y)) <= r)
        {
            ctx.arc(x, y, 4, 0, 2*Math.PI, true);
            ctx.strokeStyle = 'cyan';
            ctx.stroke();
            ctx.fillStyle   = 'cyan';
            ctx.fill();
            pi++;
        }

        else
        {
            ctx.arc(x, y, 4, 0, 2*Math.PI, true);
            ctx.strokeStyle = 'red';
            ctx.stroke();
            ctx.fillStyle   = 'red';
            ctx.fill();
        }
    }

    pi *= 4/darts;
    pi = pi.toString();

    var _ = document.createElement("p");
    var txt = document.createTextNode("Pi Estimate: " + pi);
    _.appendChild(txt);
    var e = document.getElementById("pi_approx");
    e.innerHTML = '';
    e.appendChild(_);
}

window.addEventListener("load", Initiate);