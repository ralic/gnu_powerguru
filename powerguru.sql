-- 
--   Copyright (C) 2005 Free Software Foundation, Inc.
--
--   This program is free software; you can redistribute it and/or modify
--   it under the terms of the GNU General Public License as published by
--   the Free Software Foundation; either version 2 of the License, or
--   (at your option) any later version.
--
--   This program is distributed in the hope that it will be useful,
--   but WITHOUT ANY WARRANTY; without even the implied warranty of
--   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--   GNU General Public License for more details.
--
--   You should have received a copy of the GNU General Public License
--   along with this program; if not, write to the Free Software
--   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
--

-- MySQL dump 10.8
--
-- Host: darkstar    Database: powerguru
-- ------------------------------------------------------
-- Server version	4.1.7

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE="NO_AUTO_VALUE_ON_ZERO" */;

--
-- Table structure for table `meters`
--

DROP TABLE IF EXISTS `meters`;
CREATE TABLE `meters` (
  `unit` int(11) NOT NULL default '0',
  `device_type` enum('NONE','MX','FX','SW') NOT NULL default 'NONE',
  `timestamp` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `charge_amps` int(11) NOT NULL default '0',
  `ac_load_amps` int(11) NOT NULL default '0',
  `battery_volts` float NOT NULL default '0',
  `ac_volts_out` float NOT NULL default '0',
  `ac1_volts_in` float NOT NULL default '0',
  `ac2_volts_in` float NOT NULL default '0',
  `pv_amps_in` int(11) NOT NULL default '0',
  `pv_volts_in` float NOT NULL default '0',
  `buy_amps` int(11) NOT NULL default '0',
  `sell_amps` int(11) NOT NULL default '0',
  `daily_kwh` float NOT NULL default '0',
  `hertz` int(11) NOT NULL default '0',
  `battery_tempcomp` float NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='Stores data from data logging output';

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

