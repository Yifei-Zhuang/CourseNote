package com.htl.secure_programming.utils;


import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import org.springframework.stereotype.Component;

import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.util.Base64;
import java.util.Date;

@Component
public class JwtUtil {
    private static final String JWT_SECERT = "asdhakjsgdjsavhjbbaskjchjakjsbcagghasdfavhfi2qy83rt1278figi13u2gf9812tv1ig32uohv12vy1ivg21io3hvo32y1i9v8t1g2vu9o32gh1v3g29fo13o9vg193fg1c98f89c1skd";


    public static String createJWT(String id, int userId, Long ttlMillis) throws IOException {
        long nowMillis = System.currentTimeMillis();
        Date now = new Date(nowMillis);
        SecretKey secretKey = generalKey();
        JwtBuilder builder = Jwts.builder()
                .setId(id)
                .setSubject("" + userId)
                .setIssuer("htl")
                .setIssuedAt(now)
                .signWith(SignatureAlgorithm.HS256, secretKey);
        if (ttlMillis > 0) {
            long expMillis = nowMillis + ttlMillis;
            Date expDate = new Date(expMillis);
            builder.setExpiration(expDate);
        }
        return "Bearer " + builder.compact();
    }


    public static int validateJWT(String jwtStr) throws IOException {
        String userId = parseJWT(jwtStr).getSubject();
        return Integer.parseInt(userId);
    }

    private static SecretKey generalKey() throws IOException {
        Base64.Decoder decoder = Base64.getDecoder();
        byte[] encodedKey = decoder.decode(JWT_SECERT);
        return new SecretKeySpec(encodedKey, 0, encodedKey.length, "HmacSHA256");
    }


    public static Claims parseJWT(String jwt) throws IOException {
        SecretKey secretKey = generalKey();
        jwt = jwt.split(" ")[1].trim();
        try {
            return Jwts.parser()
                    .setSigningKey(secretKey)
                    .parseClaimsJws(jwt)
                    .getBody();
        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }
    }
}