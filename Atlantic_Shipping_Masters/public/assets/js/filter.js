var input = document.getElementById("filter");
input.onkeyup = () => {
    var filter = input.value.toLowerCase();
    var nodes = document.getElementsByClassName('article');
    console.log(nodes);

    for (i = 0; i < nodes.length; i++) {
        if (nodes[i].innerHTML.toLowerCase().includes(filter)) {
            nodes[i].style.display = "flex";
        } else {
            nodes[i].style.display = "none";
        }
    }
}