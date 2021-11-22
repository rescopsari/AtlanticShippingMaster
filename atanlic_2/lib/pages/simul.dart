import 'package:flutter/material.dart';
import 'package:atanlic_2/pages/httpRequest.dart';
import 'dart:core';

class Simul extends StatefulWidget {
  final String firstHarbor;
  final List<String> listHarbor;
  const Simul({Key key, @required this.firstHarbor, @required this.listHarbor}) : super(key: key);

  @override
  _Simul createState() => _Simul();
}

class _Simul extends State<Simul> {
  Future<List> futureHarbors;

  @override
  void initState() {
    super.initState();
    futureHarbors = fetchHarbors(widget.firstHarbor, widget.listHarbor);

  }


  List<Widget> displayHarbor(List list) {
    List<Widget> list_text = new List<Widget>();
    list.removeAt(0);
    for (var harbor in list){
      list_text.add(
        new Container(
          margin: EdgeInsets.fromLTRB(70, 0, 50, 0),
          child: Column( 
            children:[
              Row(
                children: [
                  Container(
                    margin: EdgeInsets.fromLTRB(20, 0, 0, 0),
                    color: Color(0xFFbe242c),
                    height: 60,
                    width: 10,
                  )
                ],
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.start,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  ClipRRect(
                    borderRadius: BorderRadius.circular(200),
                    child: Container(
                      width: 50,
                      height: 50,
                      color: Color(0xFFbe242c),
                      child: Row(mainAxisAlignment: MainAxisAlignment.center, crossAxisAlignment: CrossAxisAlignment.center, children: [Icon(Icons.anchor_rounded, color: Colors.white,)],),
                    )
                  ),
                  Container(
                    margin: EdgeInsets.fromLTRB(30, 0, 30, 0),
                    child: Text(
                    harbor,
                    style: TextStyle(
                      fontSize: 30,
                      fontWeight: FontWeight.bold, 
                      color: Color(0xFF1EACB0)
                      ),
                    )
                  ),
                ],
              )
            ]
          )
        
      ));
    }
    return list_text;
  
  }

  @override
  Widget build(BuildContext context) {
    String start_harbor = widget.firstHarbor;
    List<String> list_harbor = widget.listHarbor;
    return Scaffold(
        backgroundColor: Color(0xFFa0ebff), 
        body: SingleChildScrollView(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Container(
                child: Transform.rotate(
                  angle: 3.14 / 180*180, 
                  child: Image.asset('assets/images/37280_transparent.png'),
                ),
              ),
              Container(
                margin: EdgeInsets.fromLTRB(70, 30, 50, 0),
                child : Row(
                mainAxisAlignment: MainAxisAlignment.start,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  ClipRRect(
                    borderRadius: BorderRadius.circular(200),
                    child: Container(
                      width: 50,
                      height: 50,
                      color: Color(0xFFbe242c),
                      child: Row(mainAxisAlignment: MainAxisAlignment.center, crossAxisAlignment: CrossAxisAlignment.center, children: [Icon(Icons.emoji_flags, color: Colors.white,)],),
                    )
                  ),
                  Container(
                    margin: EdgeInsets.fromLTRB(30, 0, 30, 0),
                    child: Text(
                    start_harbor,
                    style: TextStyle(
                      fontSize: 30,
                      fontWeight: FontWeight.bold, 
                      color: Color(0xFF1EACB0)
                      ),
                    )
                  ),
                ],
                )
              ),
              
              FutureBuilder<List>(
                future: futureHarbors,
                builder: (context, snapshot) {
                  if (snapshot.hasData){
                  return Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: displayHarbor(snapshot.data),
                  );
                  } else if (snapshot.hasError){
                    print("pritish : ${snapshot.data}");
                    return Text("${snapshot.error}");
                  }
                  // By default, show a loading spinner.
                  return CircularProgressIndicator();
                },
              ),
              SizedBox(height:50),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children:[
                  FlatButton(
                    child: Text("Nouvelle simulation"),
                    onPressed: () {Navigator.of(context).pushNamed('/start');},
                  ),
                ]
              )
            ],
          ),
        )
      );
  }
}
