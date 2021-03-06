-- phpMyAdmin SQL Dump
-- version 4.0.10.18
-- https://www.phpmyadmin.net
--
-- Host: localhost:3306
-- Generation Time: May 09, 2017 at 11:28 AM
-- Server version: 5.6.35-cll-lve
-- PHP Version: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `Air_Quality`
--

-- --------------------------------------------------------

--
-- Table structure for table `Results`
--

CREATE TABLE IF NOT EXISTS `Results` (
  `Results_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Sensor_ID` int(11) NOT NULL,
  `Date` date NOT NULL,
  `Time` time NOT NULL,
  `Temperature` float NOT NULL,
  `Humidity` tinyint(4) NOT NULL,
  `CO` int(3) NOT NULL DEFAULT '0',
  `CO2` int(3) NOT NULL,
  `Particles` float NOT NULL,
  `Latitude` float NOT NULL,
  `Longitude` float NOT NULL,
  PRIMARY KEY (`Results_ID`),
  UNIQUE KEY `Results_ID` (`Results_ID`),
  KEY `Sensor_ID_2` (`Sensor_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=ascii AUTO_INCREMENT=147 ;

--
-- Dumping data for table `Results`
--

INSERT INTO `Results` (`Results_ID`, `Sensor_ID`, `Date`, `Time`, `Temperature`, `Humidity`, `CO`, `CO2`, `Particles`, `Latitude`, `Longitude`) VALUES
(88, 1, '2017-09-05', '14:17:00', 20.5, 41, 0, 218, 0, 0, 0),
(89, 1, '2017-09-05', '14:26:00', 23, 37, 0, 228, 0, 51.4923, -2.5767),
(90, 1, '2017-09-05', '14:27:00', 22.7, 37, 0, 225, 0, 51.4923, -2.5767),
(91, 1, '2017-09-05', '14:28:00', 22.4, 36, 0, 232, 0, 51.4925, -2.5765),
(92, 1, '2017-09-05', '14:29:00', 22.7, 36, 0, 418, 0, 51.4927, -2.5764),
(93, 1, '2017-09-05', '14:30:00', 21.3, 38, 0, 341, 0, 51.4928, -2.5764),
(94, 1, '2017-09-05', '14:31:00', 21.1, 39, 0, 384, 0, 51.4929, -2.5764),
(95, 1, '2017-09-05', '14:32:00', 20.3, 39, 0, 312, 0, 51.4928, -2.5763),
(96, 1, '2017-09-05', '14:33:00', 20.2, 39, 0, 317, 0, 51.4929, -2.5763),
(97, 1, '2017-09-05', '14:34:00', 19.9, 40, 0, 321, 0, 51.4928, -2.5764),
(98, 1, '2017-09-05', '14:41:00', 18, 44, 0, 201, 0, 51.493, -2.5763),
(99, 1, '2017-09-05', '14:42:00', 17.8, 45, 0, 389, 0, 51.4929, -2.5763),
(100, 1, '2017-09-05', '14:43:00', 17.2, 46, 0, 321, 0, 51.4929, -2.5763),
(101, 1, '2017-09-05', '14:44:00', 17.1, 45, 0, 293, 0, 51.493, -2.5763),
(102, 1, '2017-09-05', '14:45:00', 17.4, 45, 0, 321, 0, 51.4929, -2.5763),
(103, 1, '2017-09-05', '14:48:00', 18, 43, 0, 326, 0, 51.4936, -2.5751),
(104, 1, '2017-09-05', '14:49:00', 15.7, 47, 0, 395, 0, 51.4948, -2.5745),
(105, 1, '2017-09-05', '14:50:00', 14.8, 50, 0, 401, 0, 51.4955, -2.574),
(106, 1, '2017-09-05', '14:51:00', 14.7, 51, 0, 523, 0, 51.4959, -2.5737),
(107, 1, '2017-09-05', '14:52:00', 15.1, 50, 0, 418, 0, 51.4966, -2.5732),
(108, 1, '2017-09-05', '14:53:00', 15.2, 51, 0, 346, 0, 51.4973, -2.5729),
(109, 1, '2017-09-05', '14:54:00', 15.4, 51, 0, 373, 0, 51.498, -2.5725),
(110, 1, '2017-09-05', '14:55:00', 14.7, 50, 0, 367, 0, 51.4988, -2.5721),
(111, 1, '2017-09-05', '14:56:00', 14.6, 51, 0, 384, 0, 51.4995, -2.5716),
(112, 1, '2017-09-05', '14:57:00', 14.7, 52, 0, 351, 0, 51.5003, -2.5712),
(113, 1, '2017-09-05', '14:58:00', 15, 51, 0, 303, 0, 51.501, -2.5706),
(114, 1, '2017-09-05', '14:59:00', 15, 50, 0, 667, 0, 51.5016, -2.5699),
(115, 1, '2017-09-05', '15:00:00', 13.9, 51, 0, 373, 0, 51.5022, -2.5692),
(116, 1, '2017-09-05', '15:01:00', 14.5, 51, 0, 418, 0, 51.5029, -2.5684),
(117, 1, '2017-09-05', '15:02:00', 14.7, 51, 0, 351, 0, 51.5035, -2.5676),
(118, 1, '2017-09-05', '15:03:00', 14.8, 50, 0, 336, 0, 51.5043, -2.5667),
(119, 1, '2017-09-05', '15:04:00', 14.4, 51, 0, 346, 0, 51.5052, -2.5663),
(120, 1, '2017-09-05', '15:06:00', 15.2, 51, 0, 378, 0, 51.506, -2.5658),
(121, 1, '2017-09-05', '15:07:00', 15, 49, 0, 362, 0, 51.5068, -2.5652),
(122, 1, '2017-09-05', '15:08:00', 15.7, 50, 0, 367, 0, 51.5076, -2.5645),
(123, 1, '2017-09-05', '15:09:00', 15.7, 48, 0, 561, 0, 51.5079, -2.5636),
(124, 1, '2017-09-05', '15:10:00', 15.4, 50, 0, 713, 0, 51.5076, -2.5624),
(125, 1, '2017-09-05', '15:11:00', 16.3, 49, 0, 321, 0, 51.5075, -2.5612),
(126, 1, '2017-09-05', '15:12:00', 15.2, 50, 0, 430, 0, 51.5073, -2.5599),
(127, 1, '2017-09-05', '15:13:00', 14.7, 51, 0, 633, 0, 51.5072, -2.5588),
(128, 1, '2017-09-05', '15:14:00', 15.2, 50, 0, 437, 0, 51.5069, -2.5575),
(129, 1, '2017-09-05', '15:15:00', 15.6, 52, 0, 531, 0, 51.5065, -2.5562),
(130, 1, '2017-09-05', '15:16:00', 16, 51, 0, 449, 0, 51.506, -2.5558),
(131, 1, '2017-09-05', '15:17:00', 16.3, 48, 0, 389, 0, 51.5059, -2.5546),
(132, 1, '2017-09-05', '15:18:00', 16.1, 50, 0, 367, 0, 51.5057, -2.5534),
(133, 1, '2017-09-05', '15:19:00', 14.7, 52, 0, 462, 0, 51.5055, -2.5522),
(134, 1, '2017-09-05', '15:20:00', 14.8, 53, 0, 418, 0, 51.5051, -2.5509),
(135, 1, '2017-09-05', '15:21:00', 14.2, 53, 0, 389, 0, 51.5046, -2.5499),
(136, 1, '2017-09-05', '15:22:00', 14.2, 55, 0, 401, 0, 51.5037, -2.5494),
(137, 1, '2017-09-05', '15:23:00', 14.5, 60, 0, 285, 0, 51.5029, -2.5499),
(138, 1, '2017-09-05', '15:24:00', 16.2, 53, 0, 412, 0, 51.5022, -2.5495),
(139, 1, '2017-09-05', '15:25:00', 17, 48, 0, 321, 0, 51.5015, -2.5491),
(140, 1, '2017-09-05', '15:26:00', 18.3, 45, 0, 326, 0, 51.5008, -2.5484),
(141, 1, '2017-09-05', '15:28:00', 17.3, 49, 0, 389, 0, 51.5007, -2.5475),
(142, 1, '2017-09-05', '15:31:00', 20.3, 42, 0, 255, 0, 51.5006, -2.5466);

-- --------------------------------------------------------

--
-- Table structure for table `Sensor_nodes`
--

CREATE TABLE IF NOT EXISTS `Sensor_nodes` (
  `Sensor_ID` int(11) NOT NULL AUTO_INCREMENT,
  `Name` text NOT NULL COMMENT 'Sensor''s Name',
  PRIMARY KEY (`Sensor_ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=ascii AUTO_INCREMENT=3 ;

--
-- Dumping data for table `Sensor_nodes`
--

INSERT INTO `Sensor_nodes` (`Sensor_ID`, `Name`) VALUES
(1, 'Main Sensor'),
(2, 'Prototype');

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
