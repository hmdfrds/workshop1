-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 26, 2021 at 03:45 AM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cybercafe`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `NO` int(255) DEFAULT NULL,
  `adminID` varchar(255) NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `name` varchar(255) NOT NULL,
  `noTel` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`NO`, `adminID`, `password`, `name`, `noTel`) VALUES
(1, 'A0319001', 'asd123', 'Ahmad Firdaus', '0199152591');

-- --------------------------------------------------------

--
-- Table structure for table `allocatingcomputers`
--

CREATE TABLE `allocatingcomputers` (
  `userID` varchar(255) NOT NULL,
  `computerID` varchar(255) NOT NULL,
  `endTime` varchar(255) NOT NULL,
  `totalTime` varchar(255) NOT NULL,
  `startTime` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `computer`
--

CREATE TABLE `computer` (
  `NO` int(255) DEFAULT NULL,
  `computerID` varchar(255) NOT NULL,
  `status` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `computer`
--

INSERT INTO `computer` (`NO`, `computerID`, `status`) VALUES
(1, 'PC0319001', 'available'),
(2, 'PC0319002', 'available'),
(3, 'PC0319003', 'available'),
(4, 'PC0319004', 'available'),
(5, 'PC0319005', 'available'),
(7, 'PC0319007', 'available'),
(8, 'PC0319008', 'available'),
(9, 'PC0319009', 'available'),
(10, 'PC0319010', 'available'),
(11, 'PC0319011', 'available'),
(12, 'PC0319012', 'available');

-- --------------------------------------------------------

--
-- Table structure for table `member`
--

CREATE TABLE `member` (
  `NO` int(255) DEFAULT NULL,
  `memberID` varchar(255) NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `name` varchar(255) NOT NULL,
  `icNumber` varchar(255) NOT NULL,
  `noTel` varchar(255) NOT NULL,
  `membershipTime` varchar(255) NOT NULL,
  `day` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `member`
--

INSERT INTO `member` (`NO`, `memberID`, `password`, `name`, `icNumber`, `noTel`, `membershipTime`, `day`) VALUES
(2, 'M0319002', 'a82647b5', 'Rasammah a/l Ramasamy', '121214858742', '0199299321', '40', '59'),
(3, 'M0319003', 'asd123', 'Veenod a/l Chakra Pillay', '010429392957', '0156780228', '20', '39'),
(4, 'M0319004', '3287074e', 'Au Faye Ngan', '090232883723', '0130724807', '20', '39'),
(5, 'M0319005', '3726fae0', 'Mohammed Khusaini bin Alimi', '010237782732', '0152227688', '20', '39'),
(6, 'M0319006', '4d11cf34', 'Janaky a/l Murugayan', '090823892837', '0159072246', '20', '39'),
(7, 'M0319007', '607c6dbb', 'K. R.Munusamy', '010283788293', '0152247833', '20', '39'),
(8, 'M0319008', '75d74d35', 'Eric Liang Kat Thang', '020687648293', '0159259085', '20', '39'),
(9, 'M0319009', '922b7272', 'Loi Liat Jeng', '120387564782', '0132820062', '20', '39'),
(10, 'M0319010', 'fce790b8', 'Kiran a/l Sivakumar', '090838283723', '0154691913', '20', '39'),
(11, 'M0319011', '1f4e2447', 'Cheam Ung Fong', '120937827382', '0148305548', '20', '39'),
(12, 'M0319012', 'a4a5d552', 'siti amalina', '090238765673', '0136309571', '20', '39'),
(13, 'M0319013', '4d3806a4', 'Hj Fathuddin bin Mirza', '120836257342', '0170937223', '20', '39'),
(14, 'M0319014', '2185daab', 'Iraman bin Nik Idrus', '091276754623', '0155851897', '20', '39'),
(15, 'M0319015', 'af72d593', 'Yu Puah Rei', '682137652634', '0190091782', '20', '39'),
(16, 'M0319016', '1acc2d44', 'You Hoe Gam', '780926543512', '0156943898', '20', '39'),
(17, 'M0319017', '836538a3', 'Samsur bin Syed Ruknuddin', '990988752612', '0151155691', '20', '39'),
(18, 'M0319018', 'be4616cd', 'C. Arul', '891029398765', '0162444130', '20', '39'),
(19, 'M0319019', '6fd58f26', 'Ngeh Khay Son', '002987667851', '0154814020', '20', '39'),
(20, 'M0319020', '4c6d6469', 'Herliyana binti Che Zuhri', '062783972651', '0151384102', '20', '39'),
(21, 'M0319021', '9783c481', 'Che Abdullah bin Ikhwan', '019277656782', '0102208647', '20', '39'),
(22, 'M0319022', '9c6db72c', 'Aliah Adip binti Huzaifi', '019827365544', '0136119913', '20', '39'),
(23, 'M0319023', 'e0ae9429', 'Yau Ye Chooi', '009876255361', '0185500001', '20', '39'),
(24, 'M0319024', 'a772b536', 'M. G. Asha', '002938716723', '0166231703', '20', '39'),
(25, 'M0319025', '033c1cc8', 'Hajjah Hani binti Rais', '019288736555', '0156002150', '20', '39'),
(27, 'M0319027', 'kucing', 'hafiz', '001002060715', '0199152591', '90', '109');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `NO` int(255) NOT NULL,
  `paymentID` varchar(255) NOT NULL,
  `userID` varchar(255) NOT NULL,
  `computerID` varchar(255) NOT NULL,
  `totalTime` varchar(255) NOT NULL,
  `price` float NOT NULL,
  `date` varchar(255) NOT NULL,
  `Paid` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`NO`, `paymentID`, `userID`, `computerID`, `totalTime`, `price`, `date`, `Paid`) VALUES
(1, '180211', 'm0319002', 'PC0319001', '4:0:0', 7.5, '22/12/20', 'paid'),
(2, '180212', 'm0319003', 'PC0319005', '4:0:0', 7.5, '23/12/20', 'paid'),
(3, '180213', '003100283827', 'PC0319011', '4:0:0', 10, '23/12/20', 'paid'),
(4, '180214', '001992777364', 'PC0319008', '4:0:0', 10, '29/12/20', 'paid'),
(5, '180215', 'M0319011', 'PC0319005', '4:0:0', 7.5, '1/1/21', 'paid'),
(10, '1902110', 'M0319009', 'PC0319011', '4:0:0', 7.5, '1/1/21', 'paid'),
(11, '1902111', 'M0319010', 'PC0319012', '4:0:0', 7.5, '2/1/21', 'paid'),
(12, '1902112', 'M0319023', 'PC0319011', '4:0:0', 7.5, '5/1/21', 'paid'),
(13, '1902113', '990093821732', 'PC0319005', '4:0:0', 10, '5/1/21', 'paid'),
(14, '1902114', 'M0319020', 'PC0319009', '4:0:0', 7.5, '5/1/21', 'paid'),
(15, '1902115', 'M0319003', 'PC0319011', '4:0:0', 7.5, '5/1/21', 'paid'),
(16, '1902116', 'M0319022', 'PC0319008', '4:0:0', 7.5, '9/1/21', 'paid'),
(17, '1902117', 'M0319024', 'PC0319003', '4:0:0', 7.5, '13/1/21', 'paid'),
(18, '1902118', '001993929323', 'PC0319007', '4:0:0', 10, '13/1/21', 'paid'),
(19, '1902119', '992837726632', 'PC0319009', '4:0:0', 10, '14/1/21', 'paid'),
(20, '1902120', '992883726612', 'PC0319004', '4:0:0', 10, '15/1/21', 'paid'),
(21, '1902121', '009927361234', 'PC0319009', '4:0:0', 10, '15/1/21', 'paid'),
(22, '1902122', '001992336623', 'PC0319010', '4:0:0', 10, '15/1/21', 'paid'),
(23, '1902123', '993882736623', 'PC0319009', '4:0:0', 10, '15/1/21', 'paid'),
(24, '1902124', '001992366632', 'PC0319001', '4:0:0', 10, '15/1/21', 'paid'),
(25, '1902125', '988777732412', 'PC0319010', '4:0:0', 10, '15/1/21', 'paid'),
(26, '1902126', '001020392773', 'PC0319007', '4:0:0', 10, '16/1/21', 'paid'),
(27, '1902127', 'M0319002', 'PC0319012', '4:0:0', 7.5, '17/1/21', 'paid'),
(28, '1902128', 'M0319019', 'PC0319005', '4:0:0', 7.5, '17/1/21', 'paid'),
(29, '1902129', '988883723612', 'PC0319008', '4:0:0', 10, '17/1/21', 'paid'),
(30, '1902130', '001992837265', 'PC0319004', '4:0:0', 10, '17/1/21', 'paid'),
(31, '1902131', 'M0319003', 'PC0319001', '4:0:0', 7.5, '17/1/21', 'paid'),
(32, '1902132', 'M0319021', 'PC0319009', '4:0:0', 7.5, '17/1/21', 'paid'),
(33, '1902133', 'M0319025', 'PC0319010', '4:0:0', 7.5, '18/1/21', 'paid'),
(34, '1902134', '001002000492', 'PC0319007', '4:0:0', 10, '18/1/21', 'paid'),
(35, '1902135', '002837261663', 'PC0319008', '4:0:0', 10, '18/1/21', 'paid'),
(36, '1902136', '001992938263', 'PC0319007', '4:0:0', 10, '18/1/21', 'paid'),
(37, '1902137', '001002060715', 'PC0319005', '0:7:19', 2.91, '19/1/21', 'Paid'),
(38, '1902138', 'm0319003', 'PC0319001', '1:5:0', 3.38, '19/1/21', 'Paid'),
(39, '1902139', '001992887362', 'PC0319008', '0:3:33', 1.4, '19/1/21', 'Paid'),
(40, '1902140', 'm0319003', 'PC0319001', '0:16:33', 4.95, '19/1/21', 'Paid'),
(41, '1902141', '001002398273', 'PC0319005', '0:2:44', 1.06, '19/1/21', 'Paid'),
(6, '190216', 'M0319004', 'PC0319011', '4:0:0', 7.5, '18/1/21', 'paid'),
(7, '190217', 'M0319020', 'PC0319010', '4:0:0', 7.5, '18/1/21', 'paid'),
(8, '190218', '993882736622', 'PC0319005', '4:0:0', 10, '19/1/21', 'paid'),
(9, '190219', '988887736210', 'PC0319001', '4:0:0', 10, '19/1/21', 'paid'),
(42, '2002142', 'm0319003', 'PC0319001', '-5:49:25', 5.44, '20/1/21', 'Paid');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`adminID`);

--
-- Indexes for table `computer`
--
ALTER TABLE `computer`
  ADD PRIMARY KEY (`computerID`);

--
-- Indexes for table `member`
--
ALTER TABLE `member`
  ADD PRIMARY KEY (`memberID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`paymentID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
