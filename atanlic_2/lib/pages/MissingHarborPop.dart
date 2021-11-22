import 'package:flutter/material.dart';

class MissingHarborPop extends StatelessWidget {
  final String title;
  final String content;
  final List<Widget> actions;

  MissingHarborPop({
    this.title,
    this.content,
    this.actions = const [],
  });

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text(
        this.title,
        style: Theme.of(context).textTheme.title,
      ),
      actions: this.actions,
      content: Text(
        this.content,
        style: Theme.of(context).textTheme.body2,
      ),
    );
  }
}