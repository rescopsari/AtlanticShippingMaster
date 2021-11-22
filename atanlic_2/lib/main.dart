import 'package:atanlic_2/pages/StartHarbor.dart';
import 'package:flutter/material.dart';
void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Atlantic Shipping Master',
      theme: ThemeData(fontFamily: 'font1'),
      debugShowCheckedModeBanner: false,
      color: Colors.blueGrey,
      home: homePage(),
      routes: {
        '/start': (_) => StartPage(),
        '/home': (_) => MyApp()
      },
    );
  }
}

class homePage extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Color(0xFFa0ebff),
      body: SingleChildScrollView(
        child: Column(
          children: [
            Background(
              child: Column(
                children: [ TitleSection,
                SizedBox(height: 100),
                Container(
                  padding: EdgeInsets.all(10),
                  margin: EdgeInsets.fromLTRB(10, 0, 10, 10),
                  width: double.infinity,
                  child: ClipRRect(
                    borderRadius: BorderRadius.circular(20),
                    child: FlatButton(
                      padding: EdgeInsets.all(10),
                      height: 100,
                      onPressed: (){Navigator.of(context).pushNamed('/start');}, //buton qui permets de changer de page
                      color: Color(0xFF1EACB0),
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.start,
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: [
                          Container(
                            margin: EdgeInsets.fromLTRB(10, 0, 20, 0),
                            child: Image.asset('assets/images/codeship.png'),
                          ),
                          Text("Lancer la simulation",
                            style: TextStyle(
                              fontWeight: FontWeight.bold,
                              fontFamily: 'font1',
                              fontSize: 17,
                              color: Colors.black54
                            ),
                          )
                        ],
                      )
                      ),
                    )
                ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}


class Background extends StatelessWidget{
  final Widget child;
  const Background({
    this.child
  });
  @override
  Widget build(BuildContext context) {
    return Container(
      height: MediaQuery.of(context).size.height,
      width: double.infinity,
      child: Stack(
        children : [
          Positioned(
            top: 0,
            left : 0,
            child : Container(
              width: 300,
              height: 300,
              child: ClipRRect(
                borderRadius: BorderRadius.circular(200),
                child: Image.asset("assets/images/113989-OOKJX3-520-removebg-preview.png"),
              ),
            ),
          ),
          child
        ]
      ),
    );
  }
}

Widget TitleSection = Container(
  height: 200,
  width: 400,
  child : Stack (
    children: [ 
      Positioned(
        right: 15,
        top: 80, 
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.end,
          children: [
          Text('Atlantic Shipping',
            style: TextStyle(fontSize: 25, fontFamily: 'font1'),
          ),
          Text('Master', style: TextStyle(
            fontSize: 30, 
            fontWeight: FontWeight.bold, 
            color: Color(0xFF1EACB0),
            fontFamily: 'font1'
          ),),
          ],
        ),
      ),
    ],
  )
);

