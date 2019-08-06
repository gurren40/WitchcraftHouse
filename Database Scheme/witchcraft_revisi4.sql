-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jul 29, 2019 at 05:58 PM
-- Server version: 10.1.40-MariaDB-0ubuntu0.18.04.1
-- PHP Version: 7.2.19-0ubuntu0.18.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `wr2`
--

DELIMITER $$
--
-- Functions
--
DROP FUNCTION IF EXISTS `UuidFromBin`$$
CREATE DEFINER=`admin`@`localhost` FUNCTION `UuidFromBin` (`_bin` BINARY(16)) RETURNS BINARY(36) SQL SECURITY INVOKER
RETURN LCASE(
    CONCAT_WS(
        '-',
        HEX(SUBSTR(_bin, 5, 4)),
        HEX(SUBSTR(_bin, 3, 2)),
        HEX(SUBSTR(_bin, 1, 2)),
        HEX(SUBSTR(_bin, 9, 2)),
        HEX(SUBSTR(_bin, 11))
    )
)$$

DROP FUNCTION IF EXISTS `UuidToBin`$$
CREATE DEFINER=`admin`@`localhost` FUNCTION `UuidToBin` (`_uuid` BINARY(36)) RETURNS BINARY(16) SQL SECURITY INVOKER
RETURN UNHEX(
    CONCAT(
        SUBSTR(_uuid, 15, 4),
        SUBSTR(_uuid, 10, 4),
        SUBSTR(_uuid, 1, 8),
        SUBSTR(_uuid, 20, 4),
        SUBSTR(_uuid, 25)
    )
)$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `ControlDevice`
--

DROP TABLE IF EXISTS `ControlDevice`;
CREATE TABLE IF NOT EXISTS `ControlDevice` (
  `controlDeviceID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `controlDeviceName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `controlDeviceToken` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `isControlDeviceOnline` tinyint(1) NOT NULL,
  `expireDate` date NOT NULL,
  PRIMARY KEY (`controlDeviceID`),
  KEY `userID` (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Device`
--

DROP TABLE IF EXISTS `Device`;
CREATE TABLE IF NOT EXISTS `Device` (
  `deviceID` int(11) NOT NULL AUTO_INCREMENT,
  `deviceUUID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `deviceName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `deviceToken` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `isDeviceOnline` tinyint(1) NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`deviceID`),
  UNIQUE KEY `deviceUUID` (`deviceUUID`),
  KEY `userID` (`userID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Groups`
--

DROP TABLE IF EXISTS `Groups`;
CREATE TABLE IF NOT EXISTS `Groups` (
  `groupID` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  `groupName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`groupID`),
  KEY `userID` (`userID`),
  KEY `iconID` (`iconID`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Icon`
--

DROP TABLE IF EXISTS `Icon`;
CREATE TABLE IF NOT EXISTS `Icon` (
  `iconID` int(11) NOT NULL,
  `iconName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`iconID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Log`
--

DROP TABLE IF EXISTS `Log`;
CREATE TABLE IF NOT EXISTS `Log` (
  `logID` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `timeStamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`logID`)
) ENGINE=InnoDB AUTO_INCREMENT=95 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Pin`
--

DROP TABLE IF EXISTS `Pin`;
CREATE TABLE IF NOT EXISTS `Pin` (
  `pinID` int(11) NOT NULL AUTO_INCREMENT,
  `UUID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `groupID` int(11) NOT NULL,
  `deviceID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  `pinTypeID` int(11) NOT NULL,
  `pinName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `options` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`pinID`),
  UNIQUE KEY `pinUUID` (`UUID`) USING BTREE,
  KEY `userID` (`userID`),
  KEY `groupID` (`groupID`),
  KEY `deviceID` (`deviceID`),
  KEY `iconID` (`iconID`),
  KEY `pinTypeID` (`pinTypeID`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `PinLog`
--

DROP TABLE IF EXISTS `PinLog`;
CREATE TABLE IF NOT EXISTS `PinLog` (
  `pinLogID` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `pinID` int(11) NOT NULL,
  `value` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `description` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`pinLogID`)
) ENGINE=InnoDB AUTO_INCREMENT=36753 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `PinType`
--

DROP TABLE IF EXISTS `PinType`;
CREATE TABLE IF NOT EXISTS `PinType` (
  `pinTypeID` int(11) NOT NULL,
  `pinTypeName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`pinTypeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Schedule`
--

DROP TABLE IF EXISTS `Schedule`;
CREATE TABLE IF NOT EXISTS `Schedule` (
  `scheduleID` int(11) NOT NULL AUTO_INCREMENT,
  `scheduleUUID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `pinID` int(11) NOT NULL,
  `scheduleName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `minute` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `hour` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `dayOfMonth` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `month` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `dayOfWeek` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `timeZone` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`scheduleID`),
  UNIQUE KEY `scheduleUUID` (`scheduleUUID`),
  KEY `userID` (`userID`),
  KEY `pinID` (`pinID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Shared`
--

DROP TABLE IF EXISTS `Shared`;
CREATE TABLE IF NOT EXISTS `Shared` (
  `sharedID` int(11) NOT NULL AUTO_INCREMENT,
  `sharedBy` int(11) NOT NULL,
  `sharedTo` int(11) NOT NULL,
  `groupID` int(11) DEFAULT NULL,
  `sharedName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`sharedID`),
  KEY `sharedBy` (`sharedBy`),
  KEY `sharedTo` (`sharedTo`),
  KEY `groupID` (`groupID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
CREATE TABLE IF NOT EXISTS `User` (
  `userID` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `name` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Tabel untuk entitas user';

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ControlDevice`
--
ALTER TABLE `ControlDevice`
  ADD CONSTRAINT `ControlDevice_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `User` (`userID`);

--
-- Constraints for table `Device`
--
ALTER TABLE `Device`
  ADD CONSTRAINT `Device_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `User` (`userID`);

--
-- Constraints for table `Groups`
--
ALTER TABLE `Groups`
  ADD CONSTRAINT `Groups_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `User` (`userID`),
  ADD CONSTRAINT `Groups_ibfk_2` FOREIGN KEY (`iconID`) REFERENCES `Icon` (`iconID`);

--
-- Constraints for table `Pin`
--
ALTER TABLE `Pin`
  ADD CONSTRAINT `Pin_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `User` (`userID`),
  ADD CONSTRAINT `Pin_ibfk_2` FOREIGN KEY (`groupID`) REFERENCES `Groups` (`groupID`),
  ADD CONSTRAINT `Pin_ibfk_3` FOREIGN KEY (`deviceID`) REFERENCES `Device` (`deviceID`),
  ADD CONSTRAINT `Pin_ibfk_4` FOREIGN KEY (`iconID`) REFERENCES `Icon` (`iconID`),
  ADD CONSTRAINT `Pin_ibfk_5` FOREIGN KEY (`pinTypeID`) REFERENCES `PinType` (`pinTypeID`);

--
-- Constraints for table `Schedule`
--
ALTER TABLE `Schedule`
  ADD CONSTRAINT `Schedule_ibfk_1` FOREIGN KEY (`userID`) REFERENCES `User` (`userID`),
  ADD CONSTRAINT `Schedule_ibfk_2` FOREIGN KEY (`pinID`) REFERENCES `Pin` (`pinID`);

--
-- Constraints for table `Shared`
--
ALTER TABLE `Shared`
  ADD CONSTRAINT `Shared_ibfk_2` FOREIGN KEY (`sharedBy`) REFERENCES `User` (`userID`),
  ADD CONSTRAINT `Shared_ibfk_3` FOREIGN KEY (`sharedTo`) REFERENCES `User` (`userID`),
  ADD CONSTRAINT `Shared_ibfk_4` FOREIGN KEY (`groupID`) REFERENCES `Groups` (`groupID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
