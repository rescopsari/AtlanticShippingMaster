import 'dart:async';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

Future<List> fetchHarbors(firstHarbor, listHarbor) async {
  String url_base = 'http://192.168.1.30/Atlantic_Shipping_Masters/public/atlantic_api?startHarbor=' + firstHarbor;
  String etapes = '&listHarbor=';
  for(var i=0; i < listHarbor.length; i++){
    if(i == (listHarbor.length - 1)){
      etapes = etapes + listHarbor[i];
    } else{
      etapes = etapes + listHarbor[i] + ",";
    }
  }

  String url = url_base + etapes;
   print("url utilisée pou communiquer avec l'api : ${url}");
  final response = await http.get(url);

  if (response.statusCode == 200) {
    // If the server did return a 200 OK response,
    // then parse the JSON.
    
    return jsonDecode(response.body);
  } else {
    // If the server did not return a 200 OK response,
    // then throw an exception.
    throw Exception('Failed to load harbor');
  }
}

class Port {
  final String name;

  Port({this.name});
}

