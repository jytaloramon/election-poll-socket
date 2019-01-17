INSERT INTO `tb_cargo` (`carg_nome`) VALUES ('Presidente');

INSERT INTO `tb_partido` (`part_nome`, `part_sigla`) VALUES ('Partido Democrático Trabalhista', 'PDT'), ('Partido dos Tabalhadores', 'PT'), ('Partido Social Liberal', 'PSL'), ('Rede Sustentabilidade', 'REDE'); 

INSERT INTO `tb_candidato` (`cand_id_part`, `cand_id_carg`, `cand_numero`, `cand_nome`, `cand_url_foto`) VALUES (2, 1, 13, 'Lulao', ''),  (1, 1, 12, 'Ciro', ''),  (3, 1, 17, 'Bolsonaro', ''),  (4, 1, 24, 'Marina', '');


CREATE VIEW `vw_info_candidatos` AS
SELECT 
	`cand_id`,
        `cand_numero`,
        `cand_id_part`,
        `cand_id_carg`, 
        `cand_nome`,
        `cand_url_foto`,
        `cand_historia`,
        `carg_id`,
        `carg_nome`,
        `part_id`,
        `part_nome`,
        `part_sigla`,
        count(`voto_id_cand`) AS `qt_votos`
FROM 
	`tb_candidato`
		INNER JOIN 
	`tb_cargo` ON `cand_id_carg` = `carg_id` 
		INNER JOIN
	`tb_partido` ON `cand_id_part` = `part_id`
		LEFT JOIN
	`tb_voto` ON `cand_id` = `voto_id_cand`
GROUP BY (`cand_id`);


SELECT * FROM `vw_info_candidatos`;

"INSERT INTO tb_voto(vot_id_cand) VALUES (?)";