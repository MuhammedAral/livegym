CREATE DATABASE SporSalonuDB;
GO

USE SporSalonuDB;
GO

CREATE TABLE Uyeler (
    UyeID INT PRIMARY KEY IDENTITY(1,1),
    KullaniciAdi NVARCHAR(50) UNIQUE,
    Sifre NVARCHAR(50),
    Ad NVARCHAR(50),
    Soyad NVARCHAR(50),
    Telefon NVARCHAR(15),
    Cinsiyet NVARCHAR(10) DEFAULT 'Erkek',
    Rol NVARCHAR(10) DEFAULT 'uye',
    AktifMi BIT DEFAULT 1
);
GO

-- Sisteme giris yapabilmeniz icin gereken varsayilan Admin hesabi
INSERT INTO Uyeler (KullaniciAdi, Sifre, Ad, Soyad, Telefon, Cinsiyet, Rol) 
VALUES ('admin', 'admin123', 'Sistem', 'Yoneticisi', '000', 'Erkek', 'admin');
GO

CREATE TABLE Dolaplar (
    DolapID INT PRIMARY KEY IDENTITY(1,1),
    DolapNo INT,
    Durum BIT DEFAULT 0,
    KullananUyeID INT NULL,
    Bolum NVARCHAR(10),
    FOREIGN KEY (KullananUyeID) REFERENCES Uyeler(UyeID)
);
GO

-- 50 Kadin 50 Erkek dolabini otomatik olusturan dongu
DECLARE @i INT = 1;
WHILE @i <= 50
BEGIN
    INSERT INTO Dolaplar (DolapNo, Bolum) VALUES (@i, 'Erkek');
    INSERT INTO Dolaplar (DolapNo, Bolum) VALUES (@i, 'Kadin');
    SET @i = @i + 1;
END
GO

CREATE TABLE Makineler (
    MakineID INT PRIMARY KEY IDENTITY(1,1),
    MakineAdi NVARCHAR(50),
    Durum BIT DEFAULT 0,
    KullananUyeID INT NULL,
    FOREIGN KEY (KullananUyeID) REFERENCES Uyeler(UyeID)
);
GO

-- Spor salonundaki 30 makineyi otomatik ekler
INSERT INTO Makineler (MakineAdi) VALUES 
('Kosu Bandi'), ('Kosu Bandi'),
('Eliptik Bisiklet'), ('Eliptik Bisiklet'),
('Dikey Bisiklet'), ('Dikey Bisiklet'),
('Yatay Bisiklet'), ('Yatay Bisiklet'),
('Kurek Makinesi'), ('Kurek Makinesi'),
('Bench Press'), ('Bench Press'),
('Incline Bench Press'), ('Incline Bench Press'),
('Butterfly'), ('Butterfly'),
('Lat Pulldown'), ('Lat Pulldown'),
('Seated Row'), ('Seated Row'),
('Leg Press'), ('Leg Press'),
('Leg Extension'), ('Leg Extension'),
('Leg Curl'), ('Leg Curl'),
('Cable Crossover'), ('Cable Crossover'),
('Smith Machine'), ('Smith Machine');
GO

CREATE TABLE CalisanCagri (
    CagriID INT PRIMARY KEY IDENTITY(1,1),
    UyeID INT,
    CagriZamani DATETIME DEFAULT GETDATE(),
    Durum NVARCHAR(20) DEFAULT 'Bekliyor',
    FOREIGN KEY (UyeID) REFERENCES Uyeler(UyeID)
);
GO
