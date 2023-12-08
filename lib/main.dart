import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:fota/colors.dart';
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
  String name = '';
  int size = 0;

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
    final snapshot1,
        snapshot2,
        snapshot3,
        snapshot4,
        snapshot5,
        snapshot6,
        snapshot7;
    snapshot1 = await ref.child('/details/current_version').get();
    snapshot2 = await ref.child('/details/timestamp').get();
    snapshot3 = await ref.child('/info/new_version').get();
    snapshot4 = await ref.child('/info/firmware_downloaded').get();
    snapshot5 = await ref.child('/info/firmware_flashed').get();
    snapshot6 = await ref.child('/info/name').get();
    snapshot7 = await ref.child('/info/size').get();
    setState(() {
      version = snapshot1.value.toString();
      last_modified = snapshot2.value.toString();
      new_version = snapshot3.value;
      firmware_downloaded = snapshot4.value;
      firmware_flashed = snapshot5.value;
      name = snapshot6.value;
      size = snapshot7.value;
    });
  }

  @override
  Widget build(BuildContext context) {
    _getDataFromFirebase();
    return Scaffold(
      appBar: AppBar(
        backgroundColor: AppColors.primary2,
        title: Center(
          child: Text(
            widget.title,
            textAlign: TextAlign.center,
            // style: Theme.of(context).textTheme.headline4!,
            style: TextStyle(
              color: Colors.black,
              fontSize: 25,
            ),
          ),
        ),
      ),
      body: Material(
        child: RefreshIndicator(
          onRefresh: _getDataFromFirebase,
          child: Container(
            decoration: BoxDecoration(
              // borderRadius: borderRadius ?? BorderRadius.circular(15.0),
              gradient: LinearGradient(
                colors: [AppColors.primary, AppColors.primary2],
                begin: Alignment.centerLeft,
                end: Alignment.centerRight,
              ),
            ),
            // color: Color.fromARGB(255, 112, 194, 242),
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
                      content: "${version}\nName: \"${name}\"",
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
                      content: new_version ? 'YES\nSize: ${size} Bytes' : 'NO',
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
      floatingActionButton: Container(
        height: 70.0,
        width: 70.0,
        child: FittedBox(
          child: FloatingActionButton(
            onPressed: _incrementCounter,
            tooltip: 'Increment',
            backgroundColor: AppColors.primary,
            child: const Icon(
              Icons.add,
              color: Colors.black,
            ),
          ),
        ),
      ),
    );
  }
}
