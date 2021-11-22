import 'package:flutter/material.dart';
import 'package:atanlic_2/pages/Checkpoint.dart';
import 'package:atanlic_2/pages/MissingHarborPop.dart';


class StartPage extends StatefulWidget {
  @override
  _StartPage createState() => _StartPage();
}

class _StartPage extends State {
  String _selected = '';

  void onChanged(String value) {
    setState(() {
      _selected = value;
    });
  }

  void _sendHarborToSecondScreen(BuildContext context) {
    String harbor = _selected;
    if (harbor.isEmpty) {
      makeRadios();
      showDialog(
         context : context,
         builder : (BuildContext dialogContext) {
           return MissingHarborPop(title: 'Erreur', content: 'Manque un port fdp');
         }
       );
    } else {
      Navigator.push(
          context,
          MaterialPageRoute(
            builder: (context) => Checkpoint(harbor: harbor),
          ));
    }
  }

  List<Widget> makeRadios() {
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
    for (var port in listPort) {
      list.add(new InkWell(
          onTap: () {
            onChanged(port);
          },
          child: new Ink(
            decoration: BoxDecoration(
              border: Border(
                top: BorderSide(width: 1.0, color: Colors.black),
              ),
            ),
            child: Row(children: [
              Radio(
                  value: port,
                  groupValue: _selected,
                  onChanged: (String value) {
                    onChanged(value);
                  }),
              Text(port)
            ]),
          )));
    }
    list.add(new FlatButton(
      child: Text("Validez"),
      onPressed: () {
        _sendHarborToSecondScreen(context);
      },
    ));
    return list;
  }

  @override
  Widget build(BuildContext context) {
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
                'Port de départ',
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
                  children: makeRadios(),
                ),
              ],
            )
          ])
        ])));
  }
}
