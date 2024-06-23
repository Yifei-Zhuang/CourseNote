package com.htl.secure_programming;

import java.util.Scanner;
import java.util.Scanner; // duplicate import

public class Bugs {
    public static void def(int a) {
        // unused method parameters
        return;
    }

    private void unusedMethod() {
        // unused private methods
        return;
    }

    // short method names
    private void a() {

    }

    // long method names
    // unused private method
    private void aa8123912i312g3u1k3h13khj312h3jk13h32aaaaaaaaaaaaaaaaaaaaa() {

    }

    public static void main(String[] args) {
        int a = 0;
        int b; // unused local vars
        Scanner in = new Scanner(System.in);
        try {

        } catch (Exception e) {
            // empty catch blocks
            def(a);
        }
        // always true
        if (1 == 1) {
            // empty block
        }
        // dead loop
        while (true) {

        }
    }
}
