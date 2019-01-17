CREATE DATABASE db_tse;

USE db_tse;

CREATE TABLE tb_partido(
	part_id INT AUTO_INCREMENT NOT NULL,
    part_nome VARCHAR(60) NOT NULL,
    part_sigla VARCHAR(10) NOT NULL,
    CONSTRAINT pk_partido PRIMARY KEY (part_id)
)engine = InnoDB;

CREATE TABLE tb_cargo(
    carg_id INT AUTO_INCREMENT NOT NULL,
    carg_nome VARCHAR(30) NOT NULL,
    CONSTRAINT pk_cargo PRIMARY KEY (carg_id)
)engine = InnoDB;

CREATE TABLE tb_candidato(
    cand_id INT AUTO_INCREMENT NOT NULL,
    cand_id_part INT NOT NULL,
    cand_id_carg INT NOT NULL,
    cand_numero INT NOT NULL,
    cand_nome VARCHAR(40) NOT NULL,
    cand_url_foto VARCHAR(255),
    cand_historia TEXT,
    CONSTRAINT pk_candidato PRIMARY KEY (cand_id),
    CONSTRAINT fk_candidato_part FOREIGN KEY (cand_id_part) REFERENCES tb_partido (part_id),
	CONSTRAINT fk_candidato_carg FOREIGN KEY (cand_id_carg) REFERENCES tb_cargo (carg_id)
)engine = InnoDB;

CREATE TABLE tb_voto(
    voto_id INT AUTO_INCREMENT NOT NULL,
    voto_id_cand  INT NOT NULL,
    CONSTRAINT pk_voto PRIMARY KEY (voto_id),
    CONSTRAINT fk_voto_cand FOREIGN KEY (voto_id_cand) REFERENCES tb_candidato (cand_id)
)engine = InnoDB;
