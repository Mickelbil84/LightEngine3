#version 410 core

out vec4 color;

uniform int objectID;

void main() {
    int oid = int(objectID);
    int r = (oid & 0x000000FF) >> 0;
    int g = (oid & 0x0000FF00) >> 8;
    int b = (oid & 0x00FF0000) >> 16;
    color = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);

    // Choose different, distinguishable, color for each value of objectID
    // int oid = int(objectID) % 10;
    // if (oid == 0) {
    //     color = vec4(1.0, 0.0, 0.0, 1.0);
    // } else if (oid == 1) {
    //     color = vec4(1.0, 1.0, 0.0, 1.0);
    // } else if (oid == 2) {
    //     color = vec4(0.0, 0.0, 1.0, 1.0);
    // } else if (oid == 3) {
    //     color = vec4(1.0, 1.0, 0.0, 1.0);
    // } else if (oid == 4) {
    //     color = vec4(1.0, 0.0, 1.0, 1.0);
    // } else if (oid == 5) {
    //     color = vec4(0.0, 1.0, 1.0, 1.0);
    // } else if (oid == 6) {
    //     color = vec4(1.0, 0.5, 0.0, 1.0);
    // } else if (oid == 7) {
    //     color = vec4(0.0, 1.0, 0.5, 1.0);
    // } else if (oid == 8) {
    //     color = vec4(0.5, 0.0, 1.0, 1.0);
    // } else if (oid == 9) {
    //     color = vec4(1.0, 0.0, 0.5, 1.0);
    // } else {
    //     color = vec4(0.0, 0.0, 0.0, 1.0);
    // }
}