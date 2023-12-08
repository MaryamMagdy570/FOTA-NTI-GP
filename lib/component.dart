import 'package:flutter/material.dart';
import 'colors.dart';

Widget defultFormField({
  required TextEditingController controller,
  required TextInputType type,
  Function(String)? onSubmit,
  Function(String)? onChange,
  GestureTapCallback? onTap,
  required FormFieldValidator<String>? validate,
  required String lable,
  required IconData prefix,
  IconData? suffix,
  bool obsCuretext = false,
  bool isCleckable = true,
  VoidCallback? onPressed,
}) =>
    TextFormField(
      controller: controller,
      keyboardType: type,
      obscureText: obsCuretext,
      onFieldSubmitted: onSubmit,
      onTap: onTap,
      onChanged: onChange,
      validator: validate,
      enabled: isCleckable,
      maxLines: 1,
      decoration: InputDecoration(
        hintText: lable,
        labelText: lable,
        border: OutlineInputBorder(),
        prefixIcon: Icon(
          prefix,
        ),
        suffixIcon: IconButton(
          onPressed: onPressed,
          icon: Icon(
            suffix,
          ),
        ),
      ),
    );

Widget defultTextButton({
  required VoidCallback? onPressed,
  required String text,
}) {
  return TextButton(
    onPressed: onPressed,
    child: Text(
      text.toUpperCase(),
    ),
  );
}

class GradientButton extends StatelessWidget {
  final String? text;
  final VoidCallback? onPressed;
  final List<Color>? gradientColors;
  final Color? textColor;
  final double? width, height, fontSize;
  final EdgeInsets? padding;
  final BorderRadius? borderRadius;
  final TextAlign? textAlign;
  final int? maxLines;
  final FontWeight? fontWeight;

  const GradientButton({
    super.key,
    this.text,
    this.onPressed,
    this.gradientColors,
    this.textColor,
    this.width,
    this.height,
    this.fontSize,
    this.padding,
    this.borderRadius,
    this.textAlign,
    this.maxLines,
    this.fontWeight,
  });

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: width ?? double.maxFinite,
      height: height ?? 52,
      child: GestureDetector(
        onTap: onPressed,
        child: Container(
          decoration: BoxDecoration(
            borderRadius: borderRadius ?? BorderRadius.circular(15.0),
            gradient: LinearGradient(
              colors: gradientColors ?? [AppColors.primary, AppColors.primary2],
              begin: Alignment.centerLeft,
              end: Alignment.centerRight,
            ),
          ),
          child: Center(
            child: Padding(
              padding: padding ?? const EdgeInsets.all(0),
              child: Text(
                text ?? "",
                textAlign: textAlign ?? TextAlign.center,
                maxLines: maxLines ?? 1,
                style: TextStyle(fontWeight: FontWeight.w400, fontSize: 22),
              ),
            ),
          ),
        ),
      ),
    );
  }
}

Widget InfoCard({
  final String? title,
  final String? content,
  final IconData? icon,
  final bool isPrimaryColor = true,
  required BuildContext context,
}) {
  final textTheme = isPrimaryColor
      ? Theme.of(context).primaryTextTheme
      : Theme.of(context).textTheme;
  return Card(
    elevation: 2,
    color: isPrimaryColor
        ? Theme.of(context).primaryColor
        : Theme.of(context).cardColor,
    shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.all(Radius.circular(8))),
    child: Padding(
      padding: const EdgeInsets.all(12.0),
      child: Column(
        mainAxisSize: MainAxisSize.min,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            '${title}',
            style: textTheme.headline5!.apply(fontFamily: 'Poppins'),
          ),
          const SizedBox(height: 10),
          Text(
            '${content}',
            style: textTheme.headline6,
          ),
          const Spacer(),
          Icon(
            icon,
            size: 32,
            color: textTheme.subtitle2!.color,
          ),
        ],
      ),
    ),
  );
}
