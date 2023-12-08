import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:fota/component.dart';
import 'package:fota/update.dart';
import 'firebase_options.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'FOTA',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'FOTA'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;
  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  /* Firebase */
  String version = '';
  String last_modified = '';
  bool new_version = false;
  bool firmware_downloaded = false;
  bool firmware_flashed = false;

  void _incrementCounter() {
    setState(() {
      Navigator.push(
        context,
        MaterialPageRoute(builder: (context) => const Update()),
      );
    });
  }

  Future<void> _getDataFromFirebase() async {
    DatabaseReference ref = FirebaseDatabase.instance.ref();
    final snapshot1, snapshot2, snapshot3, snapshot4, snapshot5;
    snapshot1 = await ref.child('/details/current_version').get();
    snapshot2 = await ref.child('/details/timestamp').get();
    snapshot3 = await ref.child('/info/new_version').get();
    snapshot4 = await ref.child('/info/firmware_downloaded').get();
    snapshot5 = await ref.child('/info/firmware_flashed').get();
    setState(() {
      version = snapshot1.value.toString();
      last_modified = snapshot2.value.toString();
      new_version = snapshot3.value;
      firmware_downloaded = snapshot4.value;
      firmware_flashed = snapshot5.value;
    });
  }

  @override
  Widget build(BuildContext context) {
    _getDataFromFirebase();
    return Scaffold(
      appBar: AppBar(
        title: Center(
          child: Text(
            widget.title,
            textAlign: TextAlign.center,
          ),
        ),
      ),
      body: Material(
        child: RefreshIndicator(
          onRefresh: _getDataFromFirebase,
          child: Container(
            color: Colors.grey[200],
            child: ListView(
              padding: const EdgeInsets.symmetric(horizontal: 16),
              physics: const BouncingScrollPhysics(),
              children: [
                const SizedBox(height: 10),
                GridView.count(
                  physics: const NeverScrollableScrollPhysics(),
                  shrinkWrap: true,
                  crossAxisCount: 1,
                  crossAxisSpacing: 8,
                  mainAxisSpacing: 8,
                  childAspectRatio: 4 / 2,
                  children: [
                    InfoCard(
                      title: 'Current Version',
                      content: version,
                      icon: Icons.timeline_outlined,
                      isPrimaryColor: false,
                      context: context,
                    ),
                    InfoCard(
                      title: 'Last Modified',
                      content: last_modified.length > 20
                          ? "Date: ${last_modified.substring(0, 10)}\nTime: ${last_modified.substring(11, 19)}"
                          : "",
                      icon: Icons.update,
                      isPrimaryColor: false,
                      context: context,
                    ),
                    InfoCard(
                      title: 'New Version Available',
                      content: new_version ? 'YES' : 'NO',
                      icon: Icons.event_available,
                      isPrimaryColor: false,
                      context: context,
                    ),
                    InfoCard(
                      title: 'Firmware Downloaded',
                      content: firmware_downloaded ? 'YES' : 'NO',
                      icon: Icons.download_done_outlined,
                      isPrimaryColor: false,
                      context: context,
                    ),
                    InfoCard(
                      title: 'Firmware Flashed',
                      content: firmware_flashed ? 'YES' : 'NO',
                      icon: Icons.install_desktop,
                      isPrimaryColor: false,
                      context: context,
                    ),
                  ],
                )
              ],
            ),
          ),
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
