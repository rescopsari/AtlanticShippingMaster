
// const ports = {"Cork" : {lat: 51.8959843, lng: -8.475}, "Plymouth" : {lat: 50.37, lng: -4.1475892}, "Brest" : {lat: 48.385,lng: -4.48},
//     "La Rochelle" : {lat: 46.1591351, lng: -1.2038517}, "St John's" : {lat: 47.5613, lng: -52.6911437}, "New York" : {lat: 40.6607352, lng: -74.0350327},
//     "Miami" : {lat: 25.7745527, lng: -80.1752576}, "La Havane" : {lat: 23.1335437, lng: -82.3396697}, "Dakar" : {lat: 14.6844041, lng: -17.4306225},
//     "Cap-Vert" : {lat: 16.0249347, lng: -24.6173696}, "Acores" : {lat: 38.3051345, lng: -29.2797304}, "Porto Rico" : {lat: 18.2089325, lng: -66.8660554},
//     "Port-au-Prince" : {lat: 18.5791152, lng: -72.3194794}};
listMarker = {}; listPorts = []; listPath = []; pathPorts = [];


// Initialize and add the map
function initMap() {
    var directionsService = new google.maps.DirectionsService();
    directionsDisplay = new google.maps.DirectionsRenderer();
    var mapOptions = { zoom:3.5, mapTypeId: google.maps.MapTypeId.ROADMAP, center: ports["Acores"] }
    map = new google.maps.Map(document.getElementById("map"), mapOptions);
    directionsDisplay.setMap(map);

    for (const port in ports) {
        const marker = new google.maps.Marker({
            position: ports[port],
            title: port,
            label: {text: port, color: "white"}
        });
        listMarker[port] = marker;
    }
    flightPath = new google.maps.Polyline({
        path: [],
        geodesic: true,
        strokeColor: "#FF0000",
        strokeOpacity: 1.0,
        strokeWeight: 2,
    });
    flightPath.setMap(map);
    cheminList();
    portList(false);
}

function portList(delpath = true) {

    var start = document.getElementById("portDepart");
    var portsElements = document.getElementsByClassName("port");

    if (listPath.length > 0) {
        if (delpath) {
            listPath = [];
            flightPath.setPath(listPath);
            pathPorts = [];
        }
        let i = 1;
        for (const port in ports) {
            if (port == pathPorts[0]) {
                break;
            }
            i++;
        }
        if (i <= 13) {
            start.value = i;
        }

    }
    listMarker[start.options[start.selectedIndex].text].setMap(map);
    listMarker[start.options[start.selectedIndex].text].setIcon({url: "http://maps.google.com/mapfiles/ms/icons/green-dot.png", labelOrigin: new google.maps.Point(15, 35)});

    listPorts = [start.value];

    for (const port of portsElements) {
        var element = port.getElementsByTagName("input")[0];
        if (element.value == start.value) {
            element.checked = false;
            port.style.display = "none";
        } else {
            port.style.display = "flex";
            if ((element.checked) || (pathPorts.includes(element.id))) {
                listPorts.push(element.value);
                listMarker[element.id].setIcon({url: "http://maps.google.com/mapfiles/ms/icons/blue-dot.png", labelOrigin: new google.maps.Point(15, 35)});
                listMarker[element.id].setMap(map);
            } else {
                listMarker[element.id].setMap(null);
            }
        }
    }
    // listPorts.push(start.value);
    // console.log("ports : ", listPorts);

}


function validateForm() {
    if (listPorts.length >= 3) {
        return true;
    } else {
        alert("Veuillez Sélectionner " + (3-listPorts.length) + " Port(s) supplémentaire !");
        return false;
    }
}