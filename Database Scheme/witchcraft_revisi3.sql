-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Apr 21, 2019 at 04:21 AM
-- Server version: 10.3.14-MariaDB
-- PHP Version: 7.3.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `witchcraft`
--

DELIMITER $$
--
-- Functions
--
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

CREATE TABLE `ControlDevice` (
  `controlDeviceID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `controlDeviceName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `controlDeviceToken` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `isControlDeviceOnline` tinyint(1) NOT NULL,
  `expireDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Device`
--

CREATE TABLE `Device` (
  `deviceID` int(11) NOT NULL,
  `deviceUUID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `deviceName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `deviceToken` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `isDeviceOnline` tinyint(1) NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Groups`
--

CREATE TABLE `Groups` (
  `groupID` int(11) NOT NULL,
  `userID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  `groupName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Icon`
--

CREATE TABLE `Icon` (
  `iconID` int(11) NOT NULL,
  `iconName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Log`
--

CREATE TABLE `Log` (
  `logID` int(11) NOT NULL,
  `userID` int(11) NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `timeStamp` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Pin`
--

CREATE TABLE `Pin` (
  `pinID` int(11) NOT NULL,
  `UUID` binary(16) NOT NULL,
  `userID` int(11) NOT NULL,
  `groupID` int(11) NOT NULL,
  `deviceID` int(11) NOT NULL,
  `iconID` int(11) NOT NULL,
  `pinTypeID` int(11) NOT NULL,
  `pinName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `options` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` text COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `PinType`
--

CREATE TABLE `PinType` (
  `pinTypeID` int(11) NOT NULL,
  `pinTypeName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Schedule`
--

CREATE TABLE `Schedule` (
  `scheduleID` int(11) NOT NULL,
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
  `description` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Shared`
--

CREATE TABLE `Shared` (
  `sharedID` int(11) NOT NULL,
  `sharedBy` int(11) NOT NULL,
  `sharedTo` int(11) NOT NULL,
  `groupID` int(11) DEFAULT NULL,
  `sharedName` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `description` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `User`
--

CREATE TABLE `User` (
  `userID` int(11) NOT NULL,
  `email` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `name` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Tabel untuk entitas user';

--
-- Indexes for dumped tables
--

--
-- Indexes for table `ControlDevice`
--
ALTER TABLE `ControlDevice`
  ADD PRIMARY KEY (`controlDeviceID`),
  ADD KEY `userID` (`userID`);

--
-- Indexes for table `Device`
--
ALTER TABLE `Device`
  ADD PRIMARY KEY (`deviceID`),
  ADD UNIQUE KEY `deviceUUID` (`deviceUUID`),
  ADD KEY `userID` (`userID`);

--
-- Indexes for table `Groups`
--
ALTER TABLE `Groups`
  ADD PRIMARY KEY (`groupID`),
  ADD KEY `userID` (`userID`),
  ADD KEY `iconID` (`iconID`);

--
-- Indexes for table `Icon`
--
ALTER TABLE `Icon`
  ADD PRIMARY KEY (`iconID`);

--
-- Indexes for table `Log`
--
ALTER TABLE `Log`
  ADD PRIMARY KEY (`logID`);

--
-- Indexes for table `Pin`
--
ALTER TABLE `Pin`
  ADD PRIMARY KEY (`pinID`),
  ADD UNIQUE KEY `pinUUID` (`UUID`) USING BTREE,
  ADD KEY `userID` (`userID`),
  ADD KEY `groupID` (`groupID`),
  ADD KEY `deviceID` (`deviceID`),
  ADD KEY `iconID` (`iconID`),
  ADD KEY `pinTypeID` (`pinTypeID`);

--
-- Indexes for table `PinType`
--
ALTER TABLE `PinType`
  ADD PRIMARY KEY (`pinTypeID`);

--
-- Indexes for table `Schedule`
--
ALTER TABLE `Schedule`
  ADD PRIMARY KEY (`scheduleID`),
  ADD UNIQUE KEY `scheduleUUID` (`scheduleUUID`),
  ADD KEY `userID` (`userID`),
  ADD KEY `pinID` (`pinID`);

--
-- Indexes for table `Shared`
--
ALTER TABLE `Shared`
  ADD PRIMARY KEY (`sharedID`),
  ADD KEY `sharedBy` (`sharedBy`),
  ADD KEY `sharedTo` (`sharedTo`),
  ADD KEY `groupID` (`groupID`);

--
-- Indexes for table `User`
--
ALTER TABLE `User`
  ADD PRIMARY KEY (`userID`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Device`
--
ALTER TABLE `Device`
  MODIFY `deviceID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Groups`
--
ALTER TABLE `Groups`
  MODIFY `groupID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Icon`
--
ALTER TABLE `Icon`
  MODIFY `iconID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Log`
--
ALTER TABLE `Log`
  MODIFY `logID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Pin`
--
ALTER TABLE `Pin`
  MODIFY `pinID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `PinType`
--
ALTER TABLE `PinType`
  MODIFY `pinTypeID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Schedule`
--
ALTER TABLE `Schedule`
  MODIFY `scheduleID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Shared`
--
ALTER TABLE `Shared`
  MODIFY `sharedID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `User`
--
ALTER TABLE `User`
  MODIFY `userID` int(11) NOT NULL AUTO_INCREMENT;

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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
