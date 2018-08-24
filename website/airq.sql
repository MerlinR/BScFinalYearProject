-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 28, 2017 at 08:41 PM
-- Server version: 5.5.54-0+deb8u1
-- PHP Version: 5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `Air_quality`
--

-- --------------------------------------------------------

--
-- Table structure for table `Results`
--

CREATE TABLE IF NOT EXISTS `Results` (
`Results_ID` int(11) NOT NULL,
  `Sensor_ID` int(11) NOT NULL,
  `Date` date NOT NULL,
  `Time` time NOT NULL,
  `Temperature` float NOT NULL,
  `Humidity` tinyint(4) NOT NULL,
  `CO` int(3) NOT NULL,
  `CO2` int(3) NOT NULL,
  `Particles` float NOT NULL,
  `Latitude` float NOT NULL,
  `Latitude_orin` char(1) NOT NULL,
  `Longitude` float NOT NULL,
  `Longitude_orin` char(1) NOT NULL COMMENT 'Longitude orientation'
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=ascii;

--
-- Dumping data for table `Results`
--

INSERT INTO `Results` (`Results_ID`, `Sensor_ID`, `Date`, `Time`, `Temperature`, `Humidity`, `CO`, `CO2`, `Particles`, `Latitude`, `Latitude_orin`, `Longitude`, `Longitude_orin`) VALUES
(1, 2, '2017-03-16', '11:18:24', 23, 54, 34, 23, 3019, 90.9, 'N', 90.9, 'E'),
(4, 1, '2017-03-22', '12:00:32', 17, 75, 100, 45, 3000, 423.32, 'N', 356.32, 'E');

-- --------------------------------------------------------

--
-- Table structure for table `Sensor_nodes`
--

CREATE TABLE IF NOT EXISTS `Sensor_nodes` (
`Sensor_ID` int(11) NOT NULL,
  `Name` text NOT NULL COMMENT 'Sensor''s Name'
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=ascii;

--
-- Dumping data for table `Sensor_nodes`
--

INSERT INTO `Sensor_nodes` (`Sensor_ID`, `Name`) VALUES
(1, 'Main Sensor'),
(2, 'Prototype');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Results`
--
ALTER TABLE `Results`
 ADD PRIMARY KEY (`Results_ID`), ADD UNIQUE KEY `Sensor_ID` (`Sensor_ID`);

--
-- Indexes for table `Sensor_nodes`
--
ALTER TABLE `Sensor_nodes`
 ADD PRIMARY KEY (`Sensor_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Results`
--
ALTER TABLE `Results`
MODIFY `Results_ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT for table `Sensor_nodes`
--
ALTER TABLE `Sensor_nodes`
MODIFY `Sensor_ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `Results`
--
ALTER TABLE `Results`
ADD CONSTRAINT `Results` FOREIGN KEY (`Sensor_ID`) REFERENCES `Sensor_nodes` (`Sensor_ID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
