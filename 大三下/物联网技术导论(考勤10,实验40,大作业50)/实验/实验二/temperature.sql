/*
 Navicat MySQL Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033
 Source Host           : localhost:3306
 Source Schema         : temperature

 Target Server Type    : MySQL
 Target Server Version : 80033
 File Encoding         : 65001

 Date: 22/03/2024 17:10:15
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for message
-- ----------------------------
DROP TABLE IF EXISTS `message`;
CREATE TABLE `message`  (
  `date` datetime(0) NOT NULL,
  `temperature` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`date`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of message
-- ----------------------------
INSERT INTO `message` VALUES ('2024-03-22 17:02:25', '23.591144271843326');
INSERT INTO `message` VALUES ('2024-03-22 17:02:30', '24.628827211333782');
INSERT INTO `message` VALUES ('2024-03-22 17:02:35', '13.880520875542572');
INSERT INTO `message` VALUES ('2024-03-22 17:02:40', '26.313729992994862');
INSERT INTO `message` VALUES ('2024-03-22 17:02:45', '26.72708290076465');
INSERT INTO `message` VALUES ('2024-03-22 17:02:50', '13.282826286414501');
INSERT INTO `message` VALUES ('2024-03-22 17:02:55', '20.952340461312605');
INSERT INTO `message` VALUES ('2024-03-22 17:03:00', '16.36562245060852');
INSERT INTO `message` VALUES ('2024-03-22 17:03:05', '15.023259979818853');
INSERT INTO `message` VALUES ('2024-03-22 17:03:10', '26.40733008970798');
INSERT INTO `message` VALUES ('2024-03-22 17:03:15', '11.3448929069025');
INSERT INTO `message` VALUES ('2024-03-22 17:03:20', '22.503161227348244');
INSERT INTO `message` VALUES ('2024-03-22 17:03:25', '21.436344905616913');
INSERT INTO `message` VALUES ('2024-03-22 17:03:30', '19.321997455733424');
INSERT INTO `message` VALUES ('2024-03-22 17:03:35', '20.233969129600176');

SET FOREIGN_KEY_CHECKS = 1;
