//For the code below, specifically the Initiate, handleFiles, and uploadFile
//functions, I am going to cite the following webpage:
//https://www.smashingmagazine.com/2018/01/drag-drop-file-uploader-vanilla-js/
//because I could not for the life of me figure out how to get the drag and drop
//to play well with my python script.
function Initiate()
{
    let drop_zone = document.getElementById('drop_zone');
    ['dragenter', 'dragover', 'dragleave', 'drop']
    .forEach(eventName =>
    {
        drop_zone.addEventListener(eventName, preventDefaults, false)
    })

    function preventDefaults(e)
    {
        e.preventDefault()
        e.stopPropagation()
    }

    ['dragenter', 'dragover'].forEach(eventName =>
    {
        drop_zone.addEventListener(eventName, highlight, false)
    })

    ;['dragleave', 'drop'].forEach(eventName =>
    {
        drop_zone.addEventListener(eventName, unhighlight, false)
    })

    function highlight(e)
    {
      drop_zone.classList.add('highlight')
    }

    function unhighlight(e)
    {
      drop_zone.classList.remove('highlight')
    }

    drop_zone.addEventListener('drop', handleDrop, false)

    function handleDrop(e)
    {
        let dt = e.dataTransfer
        let files = dt.files
        handleFiles(files)
    }
}

function handleFiles(files)
{
    ([...files]).forEach(uploadFile)
}

function uploadFile(file)
{
    var url = 'cgi-bin/p4.py'
    var xhr = new XMLHttpRequest()
    var formData = new FormData()
    xhr.open('POST', url, true)
    formData.append('file', file)
    xhr.send(formData)
}

function ShowVideo(clicked_image)
{
    if(clicked_image == "red_cube")
    {
        var e = document.getElementById("red_cube_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }
    else if(clicked_image == "green_cube")
    {
        var e = document.getElementById("green_cube_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }
    else if(clicked_image == "red_sphere")
    {
        var e = document.getElementById("red_sphere_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }
    else if(clicked_image == "green_sphere")
    {
        var e = document.getElementById("green_sphere_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }
    else if(clicked_image == "maya_cube")
    {
        var e = document.getElementById("maya_cube_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }
    else
    {
        var e = document.getElementById("maya_sphere_vid")
            e.classList.toggle('hide');
            e.classList.toggle('show');
    }

}

window.addEventListener("load", Initiate);