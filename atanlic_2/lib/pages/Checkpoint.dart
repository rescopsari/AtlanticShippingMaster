import 'package:flutter/material.dart';
import 'package:atanlic_2/pages/simul.dart';
import 'dart:core';
import 'package:atanlic_2/pages/MissingHarborPop.dart';

class Checkpoint extends StatefulWidget {
  final String harbor;
  const Checkpoint({Key key, @required this.harbor}) : super(key: key);

  @override
  _Checkpoint createState() => _Checkpoint();
}

class _Checkpoint extends State<Checkpoint> {
  List<String> _checkpoints = new List();

  void _sendHarborListToSimulScreen(BuildContext context, String startHarbor) {
    String firstHarbor = startHarbor;
    List<String> listHarbor = _checkpoints;
    if (listHarbor.length < 2) {
      makeCheckboxs(startHarbor);
      showDialog(
          context: context,
          builder: (BuildContext dialogContext) {
            return MissingHarborPop(
                title: 'Erreur',
                content: 'Deux ports doivent être choisis au minimum.');
          });
    } else {
      Navigator.push(
          context,
          MaterialPageRoute(
            builder: (context) =>
                Simul(listHarbor: listHarbor, firstHarbor: firstHarbor),
          ));
    }
  }

  List<Widget> makeCheckboxs(String startHarbor) {
    List<Widget> list = new List<Widget>();
    var listPort = [
      "Cork",
      "Plymouth",
      "Brest",
      "La Rochelle",
      "St John's",
      "New York",
      "Miami",
      "La Havane",
      "Dakar",
      "Cap-Vert",
      "Acores",
      "Porto Rico",
      "Port-au-Prince"
    ];
    listPort.remove(startHarbor);
    for (var port in listPort) {
      bool value = false;
      list.add(new CheckboxListTile(
        title: Text(port),
        value: _checkpoints.contains(port),
        onChanged: (bool newValue) {
          setState(() {
            newValue ? _checkpoints.add(port) : _checkpoints.remove(port);
          });
        },
      ));
    }
    list.add(new FlatButton(
        onPressed: () {
          _sendHarborListToSimulScreen(context, startHarbor);
        },
        child: Text("Lancer la simulation")));
    return list;
  }

  @override
  Widget build(BuildContext context) {
    String start_harbor = widget.harbor;

    return Scaffold(
        backgroundColor: Color(0xFFa0ebff),
        body: SingleChildScrollView(
            child: Column(children: [
          Stack(children: [
            Positioned(
              top: 0,
              left: 0,
              child: Container(
                width: 300,
                height: 300,
                child: ClipRRect(
                  borderRadius: BorderRadius.circular(200),
                  child: Image.asset("assets/images/27142.png"),
                ),
              ),
            ),
            Positioned(
              right: 15,
              top: 80,
              child: Text(
                'Ports Etapes',
                style: TextStyle(
                    fontSize: 26,
                    fontWeight: FontWeight.bold,
                    color: Color(0xFF1EACB0)),
              ),
            ),
            Column(
              children: [
                SizedBox(height: 300),
                Column(
                  children: makeCheckboxs(start_harbor),
                ),
              ],
            )
          ])
        ])));
  }
}
