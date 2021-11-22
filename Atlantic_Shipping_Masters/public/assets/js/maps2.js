const ports = [{lat: 51.8959843, lng: -8.475}, {lat: 50.37, lng: -4.1475892}, {lat: 48.385,lng: -4.48},
    {lat: 46.1591351, lng: -1.2038517},{lat: 47.5613, lng: -52.6911437}, {lat: 40.6607352, lng: -74.0350327},
    {lat: 25.7745527, lng: -80.1752576},{lat: 23.1335437, lng: -82.3396697}, {lat: 14.6844041, lng: -17.4306225},
    {lat: 16.0249347, lng: -24.6173696}, {lat: 38.3051345, lng: -29.2797304}, {lat: 18.2089325, lng: -66.8660554},
    {lat: 18.5791152, lng: -72.3194794}];
var listMarker, map, listPorts, listPath = [], flightPath;

// Initialize and add the map
function initMap() {
    listMarker = [];
    map = new google.maps.Map(document.getElementById("map"), {
        zoom: 2,
        center: {lat: 40, lng: 0},
    });
    for (const port of ports) {
        const marker = new google.maps.Marker({
            position: port
        });
        listMarker.push(marker);
    }
    flightPath = new google.maps.Polyline({
        path: [],
        geodesic: true,
        strokeColor: "#FF0000",
        strokeOpacity: 1.0,
        strokeWeight: 2,
    });
    flightPath.setMap(map);
    portList();
}

function portList() {
    var start = document.getElementById("portDepart");
    var portsElements = document.getElementsByClassName("port");
    listMarker[start.value].setMap(map);
    listMarker[start.value].setIcon("http://maps.google.com/mapfiles/ms/icons/green-dot.png");

    listPorts = [start.value];

    for (const port of portsElements) {
        if (port.getElementsByTagName("input")[0].value == start.value) {
            port.getElementsByTagName("input")[0].checked = false;
            port.style.display = "none";
        } else {
            port.style.display = "flex";
            if (port.getElementsByTagName("input")[0].checked) {
                listPorts.push(port.getElementsByTagName("input")[0].value);
                listMarker[port.getElementsByTagName("input")[0].value].setIcon("http://maps.google.com/mapfiles/ms/icons/blue-dot.png");
                listMarker[port.getElementsByTagName("input")[0].value].setMap(map);
            } else {
                listMarker[port.getElementsByTagName("input")[0].value].setMap(null);
            }
        }
    }
    cheminList();
}

function cheminList() {
    listPath = [ports[listPorts[0]]];
    var lenPorts = listPorts.length;
    var sumD = 0;
    for (let i = 0; i < lenPorts; i++) {
        var d = 9999999999999999;
        var index = null;
        for (let j = i; j < lenPorts; j++) {
            if (i != j) {
                var distance = google.maps.geometry.spherical.computeDistanceBetween(new google.maps.LatLng(listPath[i].lat, listPath[i].lng), new google.maps.LatLng(ports[listPorts[j]].lat, ports[listPorts[j]].lng));
                if (d > distance) {
                    d = distance;
                    index = j;
                }
            }
            if (index != null) {
                console.log(d);
                sumD += d;

                if (!(listPath.includes(ports[listPorts[index]]))) {
                    listPath.push(ports[listPorts[index]]);
                }
            }
        }

    }
    console.log("total :", sumD);
    listPath.push(ports[listPorts[0]]);
    console.log(listPath);
    flightPath.setPath(listPath);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// const ports2 = {"Cork" : {lat: 51.8959843, lng: -8.475}, "Plymouth" : {lat: 50.37, lng: -4.1475892}, "Brest" : {lat: 48.385,lng: -4.48},
//     "La Rochelle" : {lat: 46.1591351, lng: -1.2038517}, "St John's" : {lat: 47.5613, lng: -52.6911437}, "New York" : {lat: 40.6607352, lng: -74.0350327},
//     "Miami" : {lat: 25.7745527, lng: -80.1752576}, "La Havane" : {lat: 23.1335437, lng: -82.3396697}, "Dakar" : {lat: 14.6844041, lng: -17.4306225},
//     "Cap-Vert" : {lat: 16.0249347, lng: -24.6173696}, "Acores" : {lat: 38.3051345, lng: -29.2797304}, "Porto Rico" : {lat: 18.2089325, lng: -66.8660554},
//     "Port-au-Prince" : {lat: 18.5791152, lng: -72.3194794}};
// var mapGraph = {"Cork" : {"Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Plymouth" : {"Cork" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Brest" : {"Cork" : 0, "Plymouth" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "La Rochelle" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "St John's" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "New York" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Miami" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "La Havane" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Dakar" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Cap-Vert" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Acores" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Acores" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Porto Rico" : 0,"Port-au-Prince" : 0},
//                 "Porto Rico" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0,"Port-au-Prince" : 0},
//                 "Port-au-Prince" : {"Cork" : 0, "Plymouth" : 0, "Brest" : 0,"La Rochelle" : 0, "St John's" : 0, "New York" : 0,"Miami" : 0, "La Havane" : 0, "Dakar" : 0, "Cap-Vert" : 0, "Acores" : 0, "Porto Rico" : 0}
//                 };
// for (let portsKey in ports2) {
//     var lat1 = ports2[portsKey].lat, lng1 = ports2[portsKey].lng;
//     var dictPort = mapGraph[portsKey];
//     for (const dictPortKey in dictPort) {
//         var lat2 = ports2[dictPortKey].lat, lng2 = ports2[dictPortKey].lng;
//         dictPort[dictPortKey] = google.maps.geometry.spherical.computeDistanceBetween(new google.maps.LatLng(lat1, lng1), new google.maps.LatLng(lat2, lng2));
//     }
// }
// console.log(mapGraph);