// Poses y ubicaciones comprobadas para el terreno ampliado.
const glm::vec3 baseVeladora = glm::vec3(8.420000076f, 0.5817062259f, -5.500999928f);
const glm::quat giroVeladora = glm::quat(0.9993411899f, 0.004422844853f, -0.0f, 0.03602224216f);
const glm::vec3 mecha = glm::vec3(8.407800674f, 0.7507091761f, -5.499502182f);
constexpr float instanteEncendido = 6.8f;

const Pista veladora = {
    Gesto::Veladora, "veladora", 51, glm::vec3(7.5f, 0.0f, -5.7f), 90.0f,
    glm::vec3(7.15f, 1.7f, -2.3f), glm::vec3(8.02f, 0.77f, -5.7f),
    {
        {0.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 9.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-30.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-32.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.6f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {4.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-130.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {4.9f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-100.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-120.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(-40.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {5.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-213.2565255f, 0.0f, 0.0f), // brazo_der
            glm::vec3(79.6932188f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f}, 0.12f},
        {6.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-202.2565255f, 0.0f, 0.0f), // brazo_der
            glm::vec3(79.6932188f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f}, 0.12f},
        {7.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-202.2565255f, 0.0f, 0.0f), // brazo_der
            glm::vec3(79.6932188f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f}, 0.12f},
        {7.9f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-213.2565255f, 0.0f, 0.0f), // brazo_der
            glm::vec3(79.6932188f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f}, 0.12f},
        {8.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-180.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(-100.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.1f},
        {9.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-130.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {9.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {11.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 9.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-30.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-32.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {13.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {13.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
    },
    {
        {"veladora-inicio", 0.0f},
        {"veladora-reverencia", 1.8f},
        {"veladora-alcance", 5.8f},
        {"veladora-encendido", 6.8f},
        {"veladora-retiro", 7.9f},
        {"veladora-final", 13.5f},
    }
};

const Pista oracion = {
    Gesto::Oracion, "oracion", 12, glm::vec3(-10.15f, 0.0f, -2.7f), 90.0f,
    glm::vec3(-7.62f, 1.7f, -0.31f), glm::vec3(-9.96f, 1.12f, -2.7f),
    {
        {0.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-31.71006505f, 61.37947449f, -43.95527601f), // brazo_der
            glm::vec3(-24.00006214f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(18.85701166f, -64.69100974f, -29.38649958f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-31.71006505f, 61.37947449f, -43.95527601f), // brazo_der
            glm::vec3(-24.00006214f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(18.85701166f, -64.69100974f, -29.38649958f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.588f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.37747728f, 57.27880649f, -42.61229689f), // brazo_der
            glm::vec3(-46.00449668f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(38.00381799f, -54.3820413f, -42.6703091f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.676f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-13.72346197f, 47.17315571f, -40.29961874f), // brazo_der
            glm::vec3(-74.74814228f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(56.70899113f, -36.41373971f, -46.41687618f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.764f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-14.99202788f, 35.25756968f, -38.50418741f), // brazo_der
            glm::vec3(-94.87398452f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(75.27087031f, -20.82892484f, -43.23926386f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.852f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-23.660571f, 26.06917574f, -37.4550362f), // brazo_der
            glm::vec3(-103.6862331f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(91.8038418f, -11.63419931f, -39.2976778f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.94f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-28.97659603f, 22.52975976f, -37.0966391f), // brazo_der
            glm::vec3(-105.2019136f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(98.66004716f, -8.908533772f, -37.62216068f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.025f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-33.08611594f, 20.86785862f, -36.9348046f), // brazo_der
            glm::vec3(-108.0806129f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(116.5332862f, -7.408900853f, -37.98133984f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.11f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-46.06533318f, 16.66597064f, -36.54068902f), // brazo_der
            glm::vec3(-111.4143121f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(160.4718931f, -2.844159072f, -40.80531912f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.195f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-66.09429943f, 11.16355659f, -36.04953695f), // brazo_der
            glm::vec3(-107.2314633f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(212.8347461f, 5.25240608f, -45.1606234f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.28f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-86.43383097f, 5.70990325f, -35.58088693f), // brazo_der
            glm::vec3(-93.95832935f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(258.5234797f, 12.14451775f, -46.59487774f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.365f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-101.9538239f, 1.608847537f, -35.23480466f), // brazo_der
            glm::vec3(-77.67384015f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(289.7831792f, 13.80153274f, -45.13733587f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.45f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-108.404883f, 0.001280126861f, -35.09973084f), // brazo_der
            glm::vec3(-69.34676721f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(301.2461217f, 13.1600815f, -44.04449535f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.75f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-108.404883f, 0.001280126861f, -35.09973084f), // brazo_der
            glm::vec3(-69.34676721f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(301.2461217f, 13.1600815f, -44.04449535f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.838888889f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-106.4850329f, 1.166479237f, -35.19763136f), // brazo_der
            glm::vec3(-72.20800175f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(298.4997027f, 14.41808538f, -44.52154309f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.927777778f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-101.5045546f, 4.353189051f, -35.46602706f), // brazo_der
            glm::vec3(-79.16707659f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(290.5966274f, 17.36901909f, -45.82998193f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.016666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-94.54082155f, 9.103527989f, -35.87089335f), // brazo_der
            glm::vec3(-87.69454045f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(277.8983495f, 20.55745043f, -47.88126874f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.105555556f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-86.41597002f, 14.86936963f, -36.37767631f), // brazo_der
            glm::vec3(-95.75795443f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(261.1691945f, 22.59606041f, -50.63858879f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.194444444f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-77.87579518f, 20.97315794f, -36.9449645f), // brazo_der
            glm::vec3(-101.9884325f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(241.9815812f, 22.55205179f, -53.86107887f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.283333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-69.82402668f, 26.68556616f, -37.51960881f), // brazo_der
            glm::vec3(-105.7407199f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(222.7207756f, 20.36894233f, -56.98701057f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.372222222f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-63.26776224f, 31.35452638f, -38.03364543f), // brazo_der
            glm::vec3(-107.2019159f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(206.0889234f, 17.00684148f, -59.43118352f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.461111111f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-58.99750065f, 34.46879553f, -38.40560046f), // brazo_der
            glm::vec3(-107.2804016f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(194.5546737f, 13.98907522f, -60.92090925f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.55f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-57.48014681f, 35.60411299f, -38.54811577f), // brazo_der
            glm::vec3(-107.1140318f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(190.2594273f, 12.74058835f, -61.42596075f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-57.48014681f, 35.60411299f, -38.54811577f), // brazo_der
            glm::vec3(-107.1140318f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(190.2594273f, 12.74058835f, -61.42596075f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.883333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-58.4930502f, 35.98758713f, -38.5971736f), // brazo_der
            glm::vec3(-106.4914943f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(190.7002067f, 12.94882972f, -63.02954574f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.966666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-61.19843349f, 36.9958699f, -38.72848741f), // brazo_der
            glm::vec3(-104.7196885f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(191.750963f, 13.42423479f, -67.35148454f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.05f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-65.09093098f, 38.40637568f, -38.91820274f), // brazo_der
            glm::vec3(-101.8911365f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(192.9993167f, 13.86035006f, -73.65910276f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.133333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-69.6719047f, 40.00538786f, -39.14246859f), // brazo_der
            glm::vec3(-98.13824803f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(194.2174672f, 13.92959793f, -81.17949621f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.216666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-74.46539294f, 41.60532893f, -39.37773445f), // brazo_der
            glm::vec3(-93.71968255f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(195.4218208f, 13.44182424f, -89.08520112f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-79.01776183f, 43.05096579f, -39.60058986f), // brazo_der
            glm::vec3(-89.06025727f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(196.7194475f, 12.46199006f, -96.53786641f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.383333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-82.87714656f, 44.21603214f, -39.78807514f), // brazo_der
            glm::vec3(-84.76066001f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(198.0814145f, 11.28915437f, -102.7483593f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.466666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-85.56605543f, 44.99291835f, -39.91725792f), // brazo_der
            glm::vec3(-81.57822899f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(199.2264411f, 10.32491778f, -106.9900707f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.55f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-86.57649313f, 45.27711227f, -39.965421f), // brazo_der
            glm::vec3(-80.34319419f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(199.704486f, 9.938183082f, -108.5623598f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.85f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-86.57649313f, 45.27711227f, -39.965421f), // brazo_der
            glm::vec3(-80.34319419f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(199.704486f, 9.938183082f, -108.5623598f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.93f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-84.42008629f, 43.04633834f, -39.59988635f), // brazo_der
            glm::vec3(-82.8642375f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(204.0588819f, 13.53901783f, -102.3088777f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.01f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-79.55772243f, 37.53029122f, -38.79949747f), // brazo_der
            glm::vec3(-87.85253639f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(216.5056586f, 18.59676437f, -85.8207122f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.09f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-74.20983458f, 30.68972017f, -37.95747858f), // brazo_der
            glm::vec3(-91.98454812f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(232.1300442f, 17.19282582f, -64.94117908f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.17f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-70.11393406f, 24.87247366f, -37.33158395f), // brazo_der
            glm::vec3(-93.93932094f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(242.4067468f, 10.42156752f, -48.52989083f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.25f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-68.51404421f, 22.44085802f, -37.08788963f), // brazo_der
            glm::vec3(-94.34949429f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(245.4542679f, 6.50597375f, -42.09085293f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.33f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-66.30191669f, 21.33919461f, -36.98032098f), // brazo_der
            glm::vec3(-97.93038489f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(246.7911818f, 5.294941083f, -37.47747337f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.41f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-61.11381428f, 18.41479789f, -36.70234252f), // brazo_der
            glm::vec3(-105.891025f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(249.2531918f, 0.9969236324f, -26.82604437f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.49f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-54.96037391f, 14.27443796f, -36.32430863f), // brazo_der
            glm::vec3(-114.4073352f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(250.1072113f, -6.34140888f, -14.63861682f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.57f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-49.72609942f, 10.13930142f, -35.96042347f), // brazo_der
            glm::vec3(-120.7300276f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(248.3078936f, -13.78417466f, -4.370942847f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.65f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-47.48765177f, 8.193999509f, -35.79271501f), // brazo_der
            glm::vec3(-123.1497997f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(246.6707246f, -17.08545012f, 0.1555831182f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {4.95f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-47.48765177f, 8.193999509f, -35.79271501f), // brazo_der
            glm::vec3(-123.1497997f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(246.6707246f, -17.08545012f, 0.1555831182f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.03f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-45.24184118f, 9.463823029f, -35.90198437f), // brazo_der
            glm::vec3(-122.5728127f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(235.6795569f, -12.66814395f, 0.01568355007f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.11f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-40.08195769f, 12.50673292f, -36.16734064f), // brazo_der
            glm::vec3(-120.4863538f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(208.2192458f, -2.993819616f, -3.950499454f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.19f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-34.52247057f, 16.18265279f, -36.49654209f), // brazo_der
            glm::vec3(-116.4783851f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(171.3746099f, 3.712574937f, -14.9423946f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.27f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-30.40461441f, 19.55113646f, -36.80913936f), // brazo_der
            glm::vec3(-111.1313852f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(134.3113397f, 1.251023318f, -27.85736025f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.35f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-28.23518582f, 21.94311652f, -37.03909134f), // brazo_der
            glm::vec3(-106.1768138f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(107.0555859f, -6.322884126f, -35.48636395f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.43f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-27.60524772f, 22.85367124f, -37.12863854f), // brazo_der
            glm::vec3(-103.9977649f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(96.45665546f, -10.32886649f, -37.51140234f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.516666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-24.004623f, 25.33385636f, -37.37887959f), // brazo_der
            glm::vec3(-102.9201386f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(91.74499289f, -12.18145541f, -38.65790082f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.603333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-17.00984847f, 31.95518005f, -38.10337483f), // brazo_der
            glm::vec3(-97.51328572f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(79.76358434f, -18.23213985f, -41.55551978f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.69f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-13.07808935f, 41.29478072f, -39.33116964f), // brazo_der
            glm::vec3(-84.80541824f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(64.76261745f, -28.94028674f, -44.8488116f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.776666667f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-15.92719177f, 51.05450633f, -41.06572691f), // brazo_der
            glm::vec3(-64.81374141f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(50.04915029f, -43.01555809f, -45.97863759f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.863333333f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-24.58015181f, 58.49003809f, -42.97569711f), // brazo_der
            glm::vec3(-40.47740515f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(33.93484891f, -57.28204059f, -40.3389299f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {5.95f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-31.71006505f, 61.37947449f, -43.95527601f), // brazo_der
            glm::vec3(-24.00006214f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(18.85701166f, -64.69100974f, -29.38649958f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {6.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(3.0f, 0.0f, 0.0f), // torso
            glm::vec3(7.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-8.0f, 0.0f, 5.0f), // brazo_izq
            glm::vec3(-24.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-31.71006505f, 61.37947449f, -43.95527601f), // brazo_der
            glm::vec3(-24.00006214f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(18.85701166f, -64.69100974f, -29.38649958f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
    },
    {
        {"oracion-inicio", 0.0f},
        {"oracion-frente", 1.45f},
        {"oracion-pecho", 2.55f},
        {"oracion-hombro-izquierdo", 3.55f},
        {"oracion-hombro-derecho", 4.65f},
        {"oracion-final", 6.5f},
    }
};

const Pista caminar = {
    Gesto::Caminar, "caminar", 44, glm::vec3(5.7f, 0.04f, 17.23f), 90.0f,
    glm::vec3(7.6f, 1.7f, 21.2f), glm::vec3(7.3f, 0.76f, 17.0f),
    {
        {0.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 0.0f}, 0.0f},
        {0.7f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 0.0f}, 0.0f},
        {5.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 0.0f}, 3.2f},
        {6.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 0.0f}, 3.2f},
        {7.3f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 0.0f}, 3.2f},
    },
    {
        {"caminar-inicio", 0.0f},
        {"caminar-primer-paso", 1.85f},
        {"caminar-paso-alterno", 2.95f},
        {"caminar-avance", 4.25f},
        {"caminar-freno", 5.5f},
        {"caminar-giro", 6.08f},
        {"caminar-final", 7.3f},
    }
};

const Pista rodillas = {
    Gesto::Rodillas, "rodillas", 1, glm::vec3(-7.6f, 0.0f, 12.3f), 90.0f,
    glm::vec3(-7.95f, 1.7f, 15.8f), glm::vec3(-6.95f, 0.74f, 12.3f),
    {
        {0.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {0.75f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(6.0f, 0.0f, 0.0f), // torso
            glm::vec3(10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {1.6f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(12.0f, 0.0f, 0.0f), // torso
            glm::vec3(8.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-22.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(55.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(-33.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-22.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(55.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(-33.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {2.5f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-48.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(110.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(18.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-48.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(110.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(18.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {3.2f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(18.0f, 0.0f, 0.0f), // torso
            glm::vec3(16.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {6.0f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(18.0f, 0.0f, 0.0f), // torso
            glm::vec3(16.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f}, 0.0f},
        {6.8f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-48.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(110.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(18.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-48.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(110.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(18.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {7.6f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(12.0f, 0.0f, 0.0f), // torso
            glm::vec3(8.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-22.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(55.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(-33.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-22.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(55.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(-33.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {8.4f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(6.0f, 0.0f, 0.0f), // torso
            glm::vec3(10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
        {9.2f, {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f}, 0.0f},
    },
    {
        {"rodillas-inicio", 0.0f},
        {"rodillas-flexion", 1.6f},
        {"rodillas-apoyo", 3.2f},
        {"rodillas-recogimiento", 6.0f},
        {"rodillas-incorporacion", 7.6f},
        {"rodillas-final", 9.2f},
    }
};

const Pista* const pistas[] = {&veladora, &oracion, &caminar, &rodillas};
