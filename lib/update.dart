import 'dart:io';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:fota/colors.dart';
import 'component.dart';
import 'package:file_picker/file_picker.dart';
import 'package:open_file/open_file.dart';
import 'package:firebase_storage/firebase_storage.dart';
import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart';
import 'package:firebase_storage/firebase_storage.dart' as firebase_storage;

class Update extends StatefulWidget {
  const Update({super.key});

  @override
  State<Update> createState() => _UpdateState();
}

class _UpdateState extends State<Update> {
  var versionController = TextEditingController();
  var keyController = TextEditingController();
  var formKey = GlobalKey<FormState>();
  var result = null;
  String result_name = "";
  int result_size = 0;
  late PlatformFile file;
  var firebase_dev_key = "123";

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: AppColors.primary2,
        title: Text(
          "Update Firmware",
          style: TextStyle(
            color: Colors.black87,
            fontSize: 25,
          ),
        ),
        leading: IconButton(
            onPressed: () {
              Navigator.pop(context);
            },
            icon: Icon(
              Icons.arrow_back_ios_new,
              color: Colors.black,
            )),
      ),
      body: Center(
        child: SingleChildScrollView(
          child: Padding(
            padding: const EdgeInsets.all(20.0),
            child: Form(
              key: formKey,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    'New Firmware',
                    style: TextStyle(
                      color: Colors.black87,
                      fontSize: 45,
                    ),
                    // style: Theme.of(context).textTheme.headline3!.copyWith(
                    //       color: Colors.black,
                    //       fontWeight: FontWeight.w100,
                    //     ),
                  ),
                  Text(
                    'Enter the new version and Upload hex file to update the firmware in main ECU',
                    style: Theme.of(context).textTheme.bodyText2!.copyWith(
                          color: Colors.grey,
                          fontSize: 15,
                        ),
                  ),
                  SizedBox(
                    height: 20.0,
                  ),
                  Container(
                    width: double.infinity,
                    height: 200,
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(20),
                      color: const Color(0xff7c94b6),
                      shape: BoxShape.rectangle,
                      image: const DecorationImage(
                        image: AssetImage('assets/logo.jpg'),
                        fit: BoxFit.fill,
                      ),
                    ),
                  ),
                  SizedBox(
                    height: 20.0,
                  ),
                  defultFormField(
                    controller: versionController,
                    type: TextInputType.emailAddress,
                    validate: (Value) {
                      if (Value!.isEmpty) {
                        return 'please enter your firmware version';
                      }
                      return null;
                    },
                    lable: 'Firmware version',
                    prefix: Icons.timeline_outlined,
                  ),
                  SizedBox(
                    height: 20.0,
                  ),
                  defultFormField(
                    controller: keyController,
                    type: TextInputType.visiblePassword,
                    validate: (Value) {
                      if (Value!.isEmpty) {
                        return 'Please enter developer key';
                      }
                      return null;
                    },
                    prefix: Icons.lock_outline_rounded,
                    obsCuretext: true,
                    lable: 'Developer Key',
                  ),
                  SizedBox(
                    height: 20.0,
                  ),
                  GradientButton(
                    onPressed: () async {
                      // print("Choose File");
                      result = await FilePicker.platform
                          .pickFiles(allowMultiple: false);

                      result_name = result.files.first.name;
                      result_size = result.files.first.size;

                      // if no file is picked
                      if (result == null) {
                        Fluttertoast.showToast(
                            msg: "File not selected!!!",
                            toastLength: Toast.LENGTH_SHORT,
                            gravity: ToastGravity.CENTER,
                            timeInSecForIosWeb: 1,
                            backgroundColor: Colors.red,
                            textColor: Colors.white,
                            fontSize: 16.0);
                      } else if (result_name.substring(
                              result_name.length - 3, result_name.length) !=
                          "hex") {
                        Fluttertoast.showToast(
                            msg: "Error!!! Please Select hex file",
                            toastLength: Toast.LENGTH_SHORT,
                            gravity: ToastGravity.CENTER,
                            timeInSecForIosWeb: 1,
                            backgroundColor: Colors.red,
                            textColor: Colors.white,
                            fontSize: 16.0);
                        result = null;
                      } else {
                        Fluttertoast.showToast(
                            msg: "File  selected successfully",
                            toastLength: Toast.LENGTH_SHORT,
                            gravity: ToastGravity.CENTER,
                            timeInSecForIosWeb: 1,
                            backgroundColor: Colors.green,
                            textColor: Colors.white,
                            fontSize: 16.0);
                      }

                      // print(result.files.first.name);
                      // print(result.files.first.size);
                      // print(result.files.first.path);
                    },
                    text: "Choose File",
                    width: MediaQuery.of(context).size.width,
                    height: 65,
                  ),
                  SizedBox(
                    height: 30.0,
                  ),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      GradientButton(
                        onPressed: () async {
                          if (formKey.currentState!.validate()) {
                            DatabaseReference ref =
                                FirebaseDatabase.instance.ref();
                            final snapshot =
                                await ref.child('/key/developer_key').get();
                            if (snapshot.exists) {
                              firebase_dev_key = snapshot.value.toString();
                            } else {
                              print('No data available.');
                            }

                            if (keyController.text == firebase_dev_key) {
                              if (result != null) {
                                print("Upload");
                                final databaseReference =
                                    FirebaseDatabase.instance.reference();
                                databaseReference.child('/details/').set({
                                  'current_version': versionController.text,
                                  'timestamp': DateTime.now().toString(),
                                });
                                databaseReference.child('/info/').set({
                                  'new_version': true,
                                  'firmware_downloaded': false,
                                  'firmware_flashed': false,
                                  'name': result_name,
                                  'size': result_size,
                                });
                                /* upload file */
                                file = result.files.first;
                                // Rename the file
                                String fileName = '/FOTA/firmware.hex';
                                firebase_storage.Reference storageReference =
                                    firebase_storage.FirebaseStorage.instance
                                        .ref()
                                        .child(fileName);
                                try {
                                  await storageReference
                                      .putFile(File(file.path!));
                                  print('File uploaded successfully!');
                                  Navigator.pop(context);
                                  Fluttertoast.showToast(
                                      msg: "File uploaded successfully",
                                      toastLength: Toast.LENGTH_SHORT,
                                      gravity: ToastGravity.CENTER,
                                      timeInSecForIosWeb: 1,
                                      backgroundColor: Colors.green,
                                      textColor: Colors.white,
                                      fontSize: 16.0);
                                  result = null;
                                  keyController.clear();
                                  versionController.clear();
                                } catch (e) {
                                  print('Error uploading file: $e');
                                  Fluttertoast.showToast(
                                      msg: "Error uploading file: $e",
                                      toastLength: Toast.LENGTH_SHORT,
                                      gravity: ToastGravity.CENTER,
                                      timeInSecForIosWeb: 1,
                                      backgroundColor: Colors.red,
                                      textColor: Colors.white,
                                      fontSize: 16.0);
                                }
                              } else {
                                Fluttertoast.showToast(
                                    msg: "Select File First!!!",
                                    toastLength: Toast.LENGTH_SHORT,
                                    gravity: ToastGravity.CENTER,
                                    timeInSecForIosWeb: 1,
                                    backgroundColor: Colors.red,
                                    textColor: Colors.white,
                                    fontSize: 16.0);
                              }
                            } else {
                              Fluttertoast.showToast(
                                  msg: "Invalid Developer Key!!!",
                                  toastLength: Toast.LENGTH_SHORT,
                                  gravity: ToastGravity.CENTER,
                                  timeInSecForIosWeb: 1,
                                  backgroundColor: Colors.red,
                                  textColor: Colors.white,
                                  fontSize: 16.0);
                            }
                          }
                        },
                        text: "Upload",
                        gradientColors: [
                          Color.fromARGB(255, 86, 64, 183),
                          Color.fromARGB(255, 86, 64, 183)
                        ],
                        width: (MediaQuery.of(context).size.width) / 2,
                        height: 40,
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}
