package com.htl.secure_programming.utils;

import cn.hutool.core.util.IdUtil;
import cn.hutool.crypto.digest.DigestUtil;

public class encryptUtils {
    private static final int PASSWORD_AND_SALT_LENGTH = 64;

    public static String getSalt() {
        return IdUtil.simpleUUID();
    }

    public static String getMd5Hex(String password, String salt) {
        return DigestUtil.md5Hex(password + salt);
    }

    public static boolean validate(String password, String salt, String md5) {
        return DigestUtil.md5Hex(password + salt).equals(md5);
    }

}
