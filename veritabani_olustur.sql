-- Spor Salonu Veritabani Olusturma Scripti
-- MSSQL Management Studio'da calistirin

CREATE DATABASE SporSalonuDB;
GO

USE SporSalonuDB;
GO

CREATE TABLE Uyeler (
    UyeID INT PRIMARY KEY IDENTITY(1,1),
    Ad NVARCHAR(50),
    Soyad NVARCHAR(50),
    Yas INT,
    Cinsiyet NVARCHAR(10),
    TelefonNo NVARCHAR(15),
    UyelikBaslangic DATE,
    UyelikBitis DATE,
    AktifMi BIT DEFAULT 1
);

CREATE TABLE Dolaplar (
    DolapID INT PRIMARY KEY IDENTITY(1,1),
    DolapNo INT,
    Durum BIT DEFAULT 0,
    KullananUyeID INT NULL,
    Bolum NVARCHAR(10),
    FOREIGN KEY (KullananUyeID) REFERENCES Uyeler(UyeID)
);

CREATE TABLE Makineler (
    MakineID INT PRIMARY KEY IDENTITY(1,1),
    MakineAdi NVARCHAR(50),
    Durum BIT DEFAULT 0
);

CREATE TABLE Calisanlar (
    CalisanID INT PRIMARY KEY IDENTITY(1,1),
    Ad NVARCHAR(50),
    Soyad NVARCHAR(50),
    Pozisyon NVARCHAR(30)
);

CREATE TABLE CalisanUyeAtama (
    AtamaID INT PRIMARY KEY IDENTITY(1,1),
    CalisanID INT,
    UyeID INT,
    FOREIGN KEY (CalisanID) REFERENCES Calisanlar(CalisanID),
    FOREIGN KEY (UyeID) REFERENCES Uyeler(UyeID)
);
GO
