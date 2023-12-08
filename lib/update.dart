import 'dart:io';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
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
  late PlatformFile file;
  var firebase_dev_key = "123";

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Update Firmware"),
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
                    style: Theme.of(context).textTheme.headline3!.copyWith(
                          color: Colors.black,
                          fontWeight: FontWeight.w100,
                        ),
                  ),
                  Text(
                    'Enter the new version and Upload hex file to update the firmware in main MCU',
                    style: Theme.of(context).textTheme.bodyText2!.copyWith(
                          color: Colors.grey,
                          fontSize: 15,
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
                      print("Choose File");
                      result = await FilePicker.platform
                          .pickFiles(allowMultiple: false);

                      // if no file is picked
                      if (result == null) {
                        Fluttertoast.showToast(
                            msg: "File not selected ",
                            toastLength: Toast.LENGTH_SHORT,
                            gravity: ToastGravity.CENTER,
                            timeInSecForIosWeb: 1,
                            backgroundColor: Colors.red,
                            textColor: Colors.white,
                            fontSize: 16.0);
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

                      // we will log the name, size and path of the
                      // first picked file (if multiple are selected)
                      print(result.files.first.name);
                      print(result.files.first.size);
                      print(result.files.first.path);
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
                                    msg: "Select File First",
                                    toastLength: Toast.LENGTH_SHORT,
                                    gravity: ToastGravity.CENTER,
                                    timeInSecForIosWeb: 1,
                                    backgroundColor: Colors.red,
                                    textColor: Colors.white,
                                    fontSize: 16.0);
                              }
                            } else {
                              Fluttertoast.showToast(
                                  msg: "Invalid Developer Key ",
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
